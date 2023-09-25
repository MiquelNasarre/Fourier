# Fourier
In this repository I'll be adding all the tools that I'm gonna be using for my TFG, currently it consists in a simple application
that using the tools provided by SFML is able to plot a 2D Fourier Series computed by a discrete number of points in $\mathbb{R}^2$.

![GUI example](https://github.com/MiquelNasarre/Fourier/assets/124403865/b76e4b34-5871-4097-8caf-3f8767895c66)

Here you can see an example of how the interface is looking right now, it only has a couple of options but it's the best tool I've
found to represent this type of fourier series so far.

## Requirements
- [Visual Studio](https://visualstudio.com) (Is mandatory for the program to be able to unite all the diffent C++ files)
- [SFML 2.6.0](https://www.sfml-dev.org/download.php) (The files needed are already included in the repository)
## How to use it
First we clone the repository into our computer and we open the solution file with Visual Studio, then we compile the only
project inside and the App should be up and running, you should compile it in 32bit (x86).
Note: if you don't operate in Windows you might have some compatibility problems with the SFML renderer.
## Math involved
Currently there's not much of that in this project, basically it computes the Fourier coefficients out of a discrete set of points,
first from the $x$ coordinate and then from the $y$ coordinate, obtaining a 2D parametric Fourier Series.
