{
  description = "Interpolation project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        pythonEnv =
          pkgs.python3.withPackages (ps: with ps; [ numpy matplotlib ]);

        cppProject = pkgs.stdenv.mkDerivation {
          pname = "interpolation";
          version = "0.1.0";
          name = "interpolation-0.1.0";

          src = ./cpp;

          nativeBuildInputs = with pkgs; [ gnumake libgcc ];

          buildInputs = with pkgs; [ gnuplot boost ];

          buildPhase = ''
            make -j $NIX_BUILD_CORES
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp build/interpolation $out/bin/
          '';
        };

        wrapperScript =
          pkgs.writeScriptBin "run-interpolation-project-with-plots" ''
            #!${pkgs.bash}/bin/bash
            set -e

            TEMP_DIR=$(mktemp -d)
            mkdir -p $TEMP_DIR/plots/data
            mkdir -p $TEMP_DIR/plots/images

            PLOTS_DIR=$TEMP_DIR/plots ${cppProject}/bin/interpolation

            for file in $TEMP_DIR/plots/data/*.gp; do
              ${pkgs.gnuplot}/bin/gnuplot -p "$file" -e "set terminal x11; replot; pause mouse close;"
            done

            rm -rf $TEMP_DIR
          '';

        pythonProject = pkgs.stdenv.mkDerivation {
          pname = "python-interpolation";
          version = "0.1.0";
          name = "python-interpolation-0.1.0";

          src = ./py;

          nativeBuildInputs = [ pythonEnv ];

          installPhase = ''
            mkdir -p $out/bin $out/lib/python
            cp -r . $out/lib/python/
            cat > $out/bin/run-python <<EOF
            #!${pythonEnv}/bin/python
            import sys
            import os

            sys.path.insert(0, '$out/lib/python')
            sys.path.insert(0, '$out/lib/python/lagrange')

            import demo
            demo.main()
            EOF
            chmod +x $out/bin/run-python
          '';
        };

      in {
        packages = {
          cpp = cppProject;
          py = pythonProject;
          default = cppProject;
        };

        apps = {
          cpp = flake-utils.lib.mkApp {
            drv = wrapperScript;
            name = "run-interpolation-project-with-plots";
          };
          py = flake-utils.lib.mkApp {
            drv = pythonProject;
            name = "run-python";
          };
          default = flake-utils.lib.mkApp {
            drv = wrapperScript;
            name = "run-interpolation-project-with-plots";
          };
        };

        devShells.default = pkgs.mkShell {
          name = "interpolation-dev-shell";

          nativeBuildInputs = with pkgs; [
            libgcc
            gnumake
            pyright
            ccache
            git
            git-filter-repo
            bear
          ];

          buildInputs = with pkgs; [ libgcc gnuplot boost pythonEnv ];

          shellHook = ''
            export CC=gcc
            export CXX=g++
            export CXXFLAGS="''${CXXFLAGS:-}"

            export CCACHE_DIR=$HOME/.ccache
            export PATH="$HOME/.ccache/bin:$PATH"

            alias c=clear

            echo "======================================"
            echo "$(g++    --version | head -n 1)"
            echo "$(make   --version | head -n 1)"
            echo "$(python --version | head -n 1)"
            echo ""
            echo "Build the project:  nix build"
            echo "Run the project:    nix run"
            echo ""
            echo "Happy coding!"
          '';
        };
      });
}
