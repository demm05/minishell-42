{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  packages = with pkgs; [
    readline
    cmake
    gcc
    bear
    gdb
  ];
  shellHook = ''zsh'';
}
