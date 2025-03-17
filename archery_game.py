def setup():
    global arrow
    global flying
    global power
    global angle
    global target_hit
    size(800, 400)
    flying = False
    target_hit = None
    power = 50
    angle = 50
    arrow = Arrow(30, 335, 0, 0)
    arrow.display()
    
    
def key_pressed():
    global arrow
    global flying
    global power
    global angle
    directions = ["w", "s", "d", "a"]
    xVel = 6 + power/10
    yVel = -4 - angle/10
    
    if key == " ":
        arrow = Arrow(30, 335, xVel, yVel)
        flying = True
    
    for direction in directions:
        if key == direction:
            shiftTraj(direction)
    
    if key == "r":
        arrow.reset()
        
def draw():
    drawBackground()
    drawTarget()
    drawPerson()
    arrow.display()
    if target_hit != None:
        winScreen(target_hit)
        
    if flying == True:
        arrow.move()
    if flying == False and arrow.x == 30:
        fill(0)
        text_size(15)
        text_align(LEFT)
        text(f"Power: {power}%, Height: {angle}%", 30, 315)
    
class Arrow:
    def __init__(self, x, y, xVel, yVel):
        self.x = x
        self.y = y
        self.xVel = xVel
        self.yVel = yVel
        
    def x(self):
        return self.x
    
    def y(self):
        return self.y
        
    def display(self):
        rect_mode(CENTER)
        no_stroke()
        x = self.x
        y = self.y
        wid = 40
        hei = 6
        dx = 20
        fill(0)
        quad(x - (dx) + 5, y,  x - (dx) - 20, y, x - (dx) - 25, y - 5, x - (dx) - 5, y - 5)
        quad(x - (dx) + 5, y,  x - (dx) - 20, y, x - (dx) - 25, y + 5, x - (dx) - 5, y + 5)
        fill(125, 105, 60)
        rect(x, y, wid, hei)
        fill(155, 155, 155)
        quad(x + dx, y, x + dx - 5, y - 8, x + dx + 20, y, x + dx - 5, y + 8)
    
    def move(self):
        global flying
        global target_hit
        self.x += self.xVel
        self.y += self.yVel
        self.yVel += .3
        if 720 <= self.x <= 735 and 260 <= self.y <= 330:
            flying = False
            if dist(self.x + 40, self.y, 760, 295) <= 12:
                target_hit = "Red"
            elif dist(self.x + 40, self.y, 760, 295) <= 27:
                target_hit = "Blue"
            elif dist(self.x + 40, self.y, 760, 295) <= 40:
                target_hit = "White"
        if self.x >= 800 or self.y <= 0:
            target_hit = "N/A"
        
    def reset(self):
        global flying
        global power
        global angle
        global target_hit
        self.x = 30
        self.y = 335
        power = 50
        angle = 50
        flying = False
        target_hit = None
        text_size(15)
        
def drawTarget():
    #poteaux
    stroke(176, 144, 40)
    stroke_weight(6)
    line(755, 385, 760, 330) 
    line(780, 390, 760, 330) 
    #cible
    rect_mode(CENTER)
    no_stroke()
    fill(255)
    ellipse(760, 295, 80, 70) 
    fill(0, 0, 255)
    ellipse(760, 295, 55, 50)
    fill(255,0,0)
    ellipse(760, 295, 25, 22)
      
def drawBackground():
    rect_mode(CORNER)
    background(39, 242, 239) #mettre le couleur de fond à bleu ciel
    
    fill (17, 212, 27)
    rect(0, 370, 800, 30) #l'herbe
    
    rect_mode(CENTER)
    fill(253, 184, 19)
    circle(800, 0, 160)
    
def drawPerson():
    rect_mode(CENTER)
    stroke(0)
    stroke_weight(3)
    line(10, 380, 18, 350)
    line(25, 380, 18, 350) #jambes
    
    stroke_weight(5)
    line(18, 335, 30, 335) 
    line(18, 335, 6, 335) #bras
    
    stroke_weight(8)
    line(18, 350, 18, 320) #torse
    
    fill(0)
    ellipse(18, 310, 15, 15) #tête

def shiftTraj(direction):
    global power
    global angle
    if direction == "w":
        if angle < 100:
            angle += 1
    elif direction == "s":
        if angle > 0:
            angle -= 1
    elif direction == "d":
        if power < 100:
            power += 1
    elif direction == "a":
        if power > 0:
            power -= 1

def winScreen(colr): #displays text depending on your shot
    global target_hit
    if colr == "White":
        txt = "Not bad."
    elif colr == "Blue":
        txt = "Nice shot!"
    elif colr == "N/A":
        txt = "You missed! Press 'R' to try again!"
    elif colr == "Red":
        txt = "WOW YOU ARE PERFECT!"
    if target_hit != None:
        text_size(40)
        fill(0)
        text_align(CENTER)
        text(txt, 400, 70)
        

        
    
    
    
    
    