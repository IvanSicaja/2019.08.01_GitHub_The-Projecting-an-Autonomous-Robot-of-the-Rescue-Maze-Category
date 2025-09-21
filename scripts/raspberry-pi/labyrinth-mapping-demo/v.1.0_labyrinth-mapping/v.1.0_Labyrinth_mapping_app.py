import turtle

wn=turtle.Screen()
wn.bgcolor("grey")
wn.title("FESB Mapping App")
wn.setup(700,700)

#Create Pen
class Pen(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("black")
        self.penup()
        self.speed(0)

#Create player
class Player(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("blue")
        self.penup()
        self.speed(0)
        self.gold=0

    def go_up(self):
       # Walk through walls
       #self.goto(self.xcor(),self.ycor() + 24)
         
       #Calculate the spot to move to
       move_to_x=player.xcor()
       move_to_y=player.ycor() + 24

       #Check if the space has a wall
       if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)

    def go_down(self):
        # Walk through walls
        #self.goto(self.xcor(),self.ycor() - 24)

        #Calculate the spot to move to
        move_to_x=player.xcor()
        move_to_y=player.ycor() -24 

        #Check if the space has a wall
        if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)


    def go_left(self):
        # Walk through walls
        #self.goto(self.xcor() - 24,self.ycor())

        #Calculate the spot to move to
        move_to_x=player.xcor() -24
        move_to_y=player.ycor() 

        #Check if the space has a wall
        if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)

    def go_right(self):
        # Walk through walls
        #self.goto(self.xcor() + 24,self.ycor())

        
        #Calculate the spot to move to
        move_to_x=player.xcor() + 24
        move_to_y=player.ycor() 
   
        #Check if the space has a wall
        if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)

#Create visited targts
class Treasure(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("circle")
        self.color("gold")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()
   
#Create levels list 
levels=[""]

#Define first level
level_1=[
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXX   XXXXXXXXXXX",
"XXXXXXXXXXX  TXXXXXXXXXXX",
"XXXXXXXXXXX   XXXX    XXX",
"XXXXXXXXXXX     XXXXX XXX",
"XXXXXXXXXXXXXXX XXXXX XXX",
"XXXXXXXXXXXXXXX       XXX",
"XXXXXXXXXXXXXXX XXXXXXXXX",
"XXXXXXX XXX P   XXXXXXXXX",
"XXXXXXX XXXXXXX XXXXXXXXX",
"XXXXXXX XXXXXXX XXXXXXXXX",
"XXXXXXX         XXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXXXX"
]

#Add targets list
treasure=[]

#Add maze to maye list
levels.append(level_1)

#Create level setup funstion
def setup_maze(level):
    for y in range(len(level)):
        for x in range(len(level[y])):
            character=level[y][x]
            #Calculate thr screen x, y coordinstes
            screen_x=-288 + (x*24)
            screen_y=288 - (y*24)

            #Check if it is an X (Representig a wall)
            if character=="X":
                pen.goto(screen_x,screen_y)
                pen.stamp()
                #Add coordinates to wall list
                walls.append((screen_x,screen_y)) 
            
            #Check if it is an P (Representig a player)
            if character=="P":
                player.goto(screen_x,screen_y)
            
            #Check if it is an T (Representig a target)
            if character=="T":
                treasure.append(Treasure(screen_x,screen_y))
 
#Create class instances
pen=Pen()
player=Player() 

#Create walls coordinate list
walls=[]

#Set up the level
setup_maze(levels[1])

#Keyboard binding
turtle.listen()
turtle.onkey(player.go_left,"Left")
turtle.onkey(player.go_right,"Right")
turtle.onkey(player.go_up,"Up")
turtle.onkey(player.go_down,"Down")

#Turn off screen updates
wn.tracer(0)

#Main game loop
while True:
    #Update screen
    wn.update()
