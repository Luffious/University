import pygame
import math
pygame.init()
sc = pygame.display.set_mode((1000, 500))
clock = pygame.time.Clock()
y, dy = 50, 4
while True:
    sc.fill((0, 0, 0))
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            exit()
    pygame.draw.rect(sc, (255, 255, 255), (10, 10, 100, 75))
    pygame.draw.aaline(sc, (0, 200, 64), [120, 85], [220, 10])
    pygame.draw.aalines(sc, (225, 225, 0), True, [[230, 85], [330, 10], [430, 85]])
    pygame.draw.polygon(sc, (125, 125, 125), [[560, 10], [590, 50], [500, 90], [440, 30]])
    pygame.draw.ellipse(sc, (64, 128, 255), (685, 10, 270, 80))
    pygame.draw.arc(sc, (28, 38, 105), (10, 420, 280, 100), 0, math.pi)
    pygame.draw.circle(sc, (230, 50, 230), (640, y), 35, 10)
    pygame.display.update()
    if y == 462:
        dy = -4
    elif y == 54:
        dy = 4
    y += dy
    clock.tick(60)
