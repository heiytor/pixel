{
  description = "Simple 2D game engine.";

  inputs = {
    nixpkgs = {
      url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz";
    };
  };

  outputs = { self, nixpkgs }:
  let
    supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
    forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
      pkgs = import nixpkgs { inherit system; };
    });
  in
  {
    devShells = forEachSupportedSystem ({ pkgs }: {
      default = pkgs.mkShell {
      packages = with pkgs; [
        zsh
        gcc
        gnumake
      ];
      shellHook = ''
        echo "Entering PIXEL development environment."
        exec zsh
      '';
      };
    });
  };
}