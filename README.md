# matviz
## a matrix visualizer

When looking for patterns in data, it is often useful to see representations of the data.
Thus this project was born.

# installing
Currently, this is a early project. We use cmake to build the project. It is a goal of mine to remain cross platform, thus, I will only be depending on the standard libraries and gtest if at all possible. 

Building should be as easy as running:
```
task.sh -r
```
and it should automate the build process for you. 

Unfortunately, we don't install into bin directories yet, so you will have to move the executable yourself out of the build folder.
Also, it is a eventual goal to support building without building the testing directories as well.
I am sure there is a cmake command line flag for this but I haven't looked into it yet.

This project isn't being actively developed right now :(
