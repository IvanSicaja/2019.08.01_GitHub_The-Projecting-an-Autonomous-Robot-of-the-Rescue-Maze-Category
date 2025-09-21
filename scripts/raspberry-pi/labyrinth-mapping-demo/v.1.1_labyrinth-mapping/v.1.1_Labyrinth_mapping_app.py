import turtle

wn=turtle.Screen()
wn.bgcolor("grey")
wn.title("FESB Mapping App")
wn.setup(1000,700)

#Register shapes
turtle.register_shape("arrowLeft.gif")
turtle.register_shape("arrowRight.gif")
turtle.register_shape("arrowUp.gif")
turtle.register_shape("arrowDown.gif") 
turtle.register_shape("R.gif") 
turtle.register_shape("G.gif") 
turtle.register_shape("O.gif") 
turtle.register_shape("T.gif")
turtle.register_shape("Obstacle.gif") 
turtle.register_shape("wall.gif")

#Create Pen
class Pen(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("wall.gif")
        self.color("red")
        self.penup()   
        self.speed(0)
        self.gold=100
 

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create player
class Player(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("arrowLeft.gif")
        self.penup()
        self.speed(0)
        self.gold=0



    #Property fot adding "WALL" to left robot's side
    def add_wallToLeftSide(self):
  
       walls.append(Pen(player.xcor() - 24,player.ycor() ))

    #Property fot adding "WALL" to Right robot's side
    def add_wallToRighttSide(self):
  
       walls.append(Pen(player.xcor() + 24,player.ycor() ))
    
    #Property fot adding "WALL" to Up robot's side
    def add_wallToUptSide(self):
  
       walls.append(Pen(player.xcor(),player.ycor() + 24))

    #Property fot adding "WALL" to Down robot's side
    def add_wallToDowntSide(self):
  
       walls.append(Pen(player.xcor(),player.ycor() - 24))

    #Property fot adding "GREEN" victim on screen
    def add_Green(self):
  
       treasure.append(GreenVictim(player.xcor(),player.ycor() ))
    
    #Property fot adding "ORANGE" victim on screen
    def add_Orange(self):
  
       treasure.append(OrangeVictim(player.xcor(),player.ycor() ))
    
    #Property fot adding "RED" victim on screen
    def add_Red(self):
  
       treasure.append(RedVictim(player.xcor(),player.ycor() ))
    
    #Property fot adding "BLACK" victim on screen
    def add_Black(self):
  
       treasure.append(BlackVictim(player.xcor(),player.ycor() ))

    #Property fot adding "Grey" victim on screen
    def add_Gray(self):
  
       treasure.append(GreyVictim(player.xcor(),player.ycor() ))

    #Property fot adding "Green Letter" victim on screen
    def add_GreenLetter(self):
  
       treasure.append(GreenLetterVictim(player.xcor(),player.ycor() ))

    #Property fot adding "Orange Letter" victim on screen
    def add_OrangeLetter(self):
  
       treasure.append(OrangeLetterVictim(player.xcor(),player.ycor() ))

    #Property fot adding "Red Letter" victim on screen
    def add_RedLetter(self):
  
       treasure.append(RedLetterVictim(player.xcor(),player.ycor() ))
    
    #Property fot adding "Temperature" victim on screen
    def add_Temperature(self):
  
       treasure.append(TemperatureVictim(player.xcor(),player.ycor() ))

    #Property fot adding "Obastacle" on screen
    def add_Obstacle(self):
  
       treasure.append(Obstacle(player.xcor(),player.ycor() )) 


    def go_up(self):
       # Walk through walls
       #self.goto(self.xcor(),self.ycor() + 24)
 
       self.shape("arrowUp.gif")   
       
       #Calculate the spot to move to
       move_to_x=player.xcor()
       move_to_y=player.ycor() + 24

       #Check if the space has a wall
       if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)

    def go_down(self):
        # Walk through walls
        #self.goto(self.xcor(),self.ycor() - 24)

        self.shape("arrowDown.gif")

        #Calculate the spot to move to
        move_to_x=player.xcor()
        move_to_y=player.ycor() -24 

        #Check if the space has a wall
        if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)


    def go_left(self):
        # Walk through walls
        #self.goto(self.xcor() - 24,self.ycor())

        self.shape("arrowRight.gif")

        #Calculate the spot to move to
        move_to_x=player.xcor() -24
        move_to_y=player.ycor() 

        #Check if the space has a wall
        if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)

    def go_right(self):
        # Walk through walls
        #self.goto(self.xcor() + 24,self.ycor())

        self.shape("arrowLeft.gif")
  
        #Calculate the spot to move to
        move_to_x=player.xcor() + 24
        move_to_y=player.ycor() 
   
        #Check if the space has a wall
        if(move_to_x,move_to_y) not in walls:
           self.goto(move_to_x,move_to_y)

             
#Create visited targts

#Create "RED" victim icon
class RedVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("circle")
        self.color("red")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "ORANGE" victim icon
class OrangeVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("circle")
        self.color("orange")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "GREEN" victim icon
class GreenVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("circle")
        self.color("green")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "GREY" victim icon
class GreyVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("circle")
        self.screen.colormode(255)
        self.color(107,107,107)
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "BLACK" victim icon
class BlackVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("circle")
        self.color("black")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "Red" letter victim icon
class RedLetterVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("R.gif")
        
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)
    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "Orange" letter victim icon
class OrangeLetterVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("O.gif")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "Green" letter victim icon
class GreenLetterVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("G.gif")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)
        self.hideturtle()

#Create "Temperature" victim icon
class TemperatureVictim(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("T.gif")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)

#Create "Obstacle"  icon
class Obstacle(turtle.Turtle):
    def __init__(self,x,y):
        turtle.Turtle.__init__(self)
        self.shape("Obstacle.gif")
        self.penup()   
        self.speed(0)
        self.gold=100
        self.goto(x,y)

    def destroy(self):
        self.goto(2000,2000)

#Create "End"  icon
class End(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("blue")
        self.penup()
        self.speed(0)  

#backpath
class Yellow(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("yellow")
        self.penup()
        self.speed(0)

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
turtle.onkey(player.add_Green,"1")
turtle.onkey(player.add_Orange,"2")
turtle.onkey(player.add_Red,"3")
turtle.onkey(player.add_GreenLetter,"4")
turtle.onkey(player.add_OrangeLetter,"5")
turtle.onkey(player.add_RedLetter,"6")
turtle.onkey(player.add_Temperature,"7")
turtle.onkey(player.add_Obstacle,"8")
turtle.onkey(player.add_Black,"9")
turtle.onkey(player.add_Gray,"0")
 

turtle.onkey(player.add_wallToRighttSide,"d")
turtle.onkey(player.add_wallToLeftSide,"a")
turtle.onkey(player.add_wallToUptSide,"w")
turtle.onkey(player.add_wallToDowntSide,"s")

#Turn off screen updates
wn.tracer(0)

#Main game loop
while True:
    #Update screen
    wn.update()
