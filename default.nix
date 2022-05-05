{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell
  {
    nativeBuildInputs = [pkgs.sbt pkgs.openjdk8 pkgs.metals];
  }
