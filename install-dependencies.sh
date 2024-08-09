#!/bin/bash

# Update Homebrew
brew update

# For development

# Install cmake
brew install cmake;

# Install IWYU
brew install include-what-you-use;

# For the product

brew install sfml

echo "All dependencies have been installed."
