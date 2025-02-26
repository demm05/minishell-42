{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  packages = with pkgs; [
    readline
    criterion
  ];
  shellHook = ''zsh'';
}
