
name = 'Darryl Davis'

collaborators = 'Spencer Waton'

print ('Homework 11, by ' + name + ' with help from ' + collaborators)

description = '''This program called Tetris, will be performed through turtles. From
the user's perspective, when they start the program, they will see a tetris piece slowly fall from the top screen until it lands
on the bottom of the screen or on top of another tetris piece.
'''

# What works currently - a few sentences
works = '''The tetris piece can slowly fall from the top screen until it lands on the bottom screen. We assigned four key buttons for rotating the piece.
We assigned two key buttons for moving it left and right as it falls to the bottom.
'''

# What does not work currently - a few sentences
broken = '''At first, we were having problems moving the piece left and right by pushing the key repetetly, but that problem was fixed with an update function.
'''

questions = '''How are we going to make a row disappear when it is filled?
Since it is up to the player to decide where each random piece goes, how can having a predetermined coordinate for each piece by telling it where to stop work?
'''
from turtle import *
import math
def moveAlittle():
## This function is suppose to move the tetris piece down a little bit at a time. And it also shows the lists of coordinates.
    global history
    
    
    forward(5)
    # This for loop checks the history.
    update()
    for xy in history:
        dx = xy[0] - xcor()
        dy = xy[1] - ycor()
        d = math.sqrt(dx**2 + dy**2)
        if d < 4:
            shape('tetrisP.gif')
            return          

    history.append( [int(xcor()), int(ycor())] )

    if ycor() > window_height()/2 or \
       ycor() < -window_height()/2:
        shape('tetrisP.gif')
    else:
        ontimer(moveAlittle,100)
    print (history)

def rotup():
    
# Rotates the piece when you push the 'e' key.
    register_shape('tetrisPL.gif')
    shape('tetrisPL.gif')

    
def rotdown():
#Rotates the piece when you push the 'd' key.
    register_shape('tetrisPR.gif')
    shape('tetrisPR.gif')
def rotleft():
#Rotates when you push the 's' key.
    register_shape('tetrisP.gif')
    shape('tetrisP.gif')
def rotright():
#Rotates when you push the 'f' key.
    register_shape('tetrisPU.gif')
    shape('tetrisPU.gif')
def sidewayr():
# Moves the piece right.
    if xcor()+50<window_width()/2:
        setx(xcor()+50)
        update()
def sidewayl():
# Moves the piece left.
    if xcor()-50>-window_width()/2:
        setx(xcor()-50)
        update()
def tetris():
# Allows for the picture of the piece to be shown when its coming down.
    global history
    history = []
    resetscreen()
    tracer(False)
    speed(1)
    register_shape('tetrisP.gif')
    shape('tetrisP.gif')
    penup()
    turtlesize(4)
    goto(0,500)
    rt(90)
    fd(250)
    onkey(rotup,'e')
    onkey(rotdown,'d')
    onkey(rotleft,'s')
    onkey(rotright,'f')
    onkey(sidewayr,'Right')
    onkey(sidewayl,'Left')
    listen()
    ontimer(moveAlittle)
    mainloop()

 
tetris()
input()
 
