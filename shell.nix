{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  packages = with pkgs; [
    readline
    criterion
    cmake
    gcc
    bear
    gdb
    norminette
  ];
  shellHook = ''zsh'';
}
