package sample;

import java.io.FileInputStream;

public class Field {

    private final int field_x = 27;
    private final int field_y = 28;
    private int countOfDots = 0;
    private boolean dotEaten = false;
    private final Cell[] field_ = new Cell[field_x*field_y];
    public Field(Entity pacman, Entity ghostA, Entity ghostB) {
        resetField(pacman, ghostA, ghostB);
    }
    public void resetField(Entity pacman, Entity ghostA, Entity ghostB){
        try (FileInputStream f = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\sample\\field.txt")) {
            byte[] objects = new byte[f.available()];
            f.read(objects, 0, f.available());
            int pacmanRotation = 0;
            int ghostARotation = 0;
            int ghostBRotation = 0;
            int c = 0;
            for(byte a: objects){

                switch (a){
                    case('o')->{
                        field_[c] = Cell.EMPTINESS;
                        c++;
                    }
                    case('w')->{
                        field_[c] = Cell.WALL;
                        c++;
                    }
                    case('p')->{
                        field_[c] = Cell.POINT;
                        countOfDots++;
                        c++;
                    }
                    case('m')->{
                        field_[c] = Cell.EMPTINESS;
                        pacmanRotation = c;
                        c++;
                    }
                    case('W')->{
                        field_[c] = Cell.GHOST_WALL;
                        c++;
                    }
                    case('A')->{
                        field_[c] =Cell.EMPTINESS;
                        ghostARotation = c;
                        c++;
                    }
                    case('B')->{
                        field_[c] =Cell.EMPTINESS;
                        ghostBRotation = c;
                        c++;
                    }
                }
            }
            pacman.setX(pacmanRotation%field_x);
            pacman.setY(pacmanRotation/field_x);

            ghostA.setX(ghostARotation%field_x);
            ghostA.setY(ghostARotation/field_x);

            ghostB.setX(ghostBRotation%field_x);
            ghostB.setY(ghostBRotation/field_x);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public int getCountOfDots(){
        return countOfDots;
    }

    public int getField_y() {
        return field_y;
    }

    public int getField_x() {
        return field_x;
    }

    public Cell[] getObjects() {
        return field_;
    }

    public Cell checkCell(int x, int y){
        if(x > field_x || x < 0){
            x = (x + field_x)%field_x;
        }
        if(y > field_y || y < 0){
            y = (y + field_y)%field_y;
        }
        return field_[x+field_x*y];
    }

    public boolean checkMovePacman(Entity pacman){
        int pacmanRotation_x = pacman.getX();
        int pacmanRotation_y = pacman.getY();
        Cell b = Cell.EMPTINESS;
        switch (pacman.getNextDirection()){
            case UP -> {
                b = field_[pacmanRotation_x+((pacmanRotation_y+field_y-1)%field_y)*field_x];

            }
            case DOWN -> {
                b = field_[pacmanRotation_x+((pacmanRotation_y+1)%field_y)*field_x];

            }
            case LEFT -> {
                b = field_[(pacmanRotation_x+field_x -1)%field_x+pacmanRotation_y*field_x];

            }
            case RIGHT -> {
                b = field_[(pacmanRotation_x+1)%field_x+pacmanRotation_y*field_x];
            }
        }
        return b != Cell.GHOST_WALL && b != Cell.WALL;
    }

    public boolean move(Entity entity){
        int entityX = entity.getX();
        int entityY = entity.getY();
        switch (entity.getDirection()){
            case UP -> {
                if(field_[entityX+((entityY+field_y-1)%field_y)*field_x] == Cell.WALL){
                    return false;
                }
                entity.setY((entityY+field_y-1)%field_y);

            }
            case DOWN -> {
                if(field_[entityX+((entityY+1)%field_y)*field_x] == Cell.WALL){
                    return false;
                }
                entity.setY((entityY+1)%field_y);
            }
            case LEFT -> {
                if(field_[(entityX+field_x -1)%field_x+entityY*field_x] == Cell.WALL){
                    return false;
                }
                entity.setX((entityX+field_x -1)%field_x);
            }
            case RIGHT -> {
                if(field_[(entityX+1)%field_x+entityY*field_x] == Cell.WALL){
                    return false;
                }
                entity.setX((entityX+1)%field_x);
            }
        }
        if(entity.getClass() == Pacman.class) {
            if (field_[entityX + entityY * field_x] == Cell.POINT) {
                countOfDots--;
                dotEaten = true;
            }
            field_[entityX + entityY * field_x] = Cell.EMPTINESS;
        }
        return true;
    }
    public boolean isDotEaten(){
        return dotEaten;
    }
    public void dotUneaten(){
        dotEaten = false;
    }
    public boolean checkMoveGhost(Entity ghost){
        int ghostRotation_x = ghost.getX();
        int ghostRotation_y = ghost.getY();
        switch (ghost.getNextDirection()){
            case UP -> {
                if(field_[ghostRotation_x+((ghostRotation_y+field_y-1)%field_y)*field_x] != Cell.WALL){
                    return true;
                }
            }
            case DOWN -> {
                if(field_[ghostRotation_x+((ghostRotation_y+1)%field_y)*field_x] != Cell.WALL){
                    return true;
                }
            }
            case LEFT -> {
                if(field_[(ghostRotation_x+field_x -1)%field_x+ghostRotation_y*field_x] != Cell.WALL){
                    return true;
                }
            }
            case RIGHT -> {
                if(field_[(ghostRotation_x+1)%field_x+ghostRotation_y*field_x] != Cell.WALL){
                    return true;
                }
            }
        }
        return false;
    }
/*
    public boolean moveGhost(Entity ghost){
        int ghostRotation_x = ghost.getX();
        int ghostRotation_y = ghost.getY();
        switch (ghost.getDirection()){
            case UP -> {
                if(field_[ghostRotation_x+((ghostRotation_y+field_y-1)%field_y)*field_x] == Cell.WALL){
                    return false;
                }
                ghost.setY((ghostRotation_y+field_y-1)%field_y);

            }
            case DOWN -> {
                if(field_[ghostRotation_x+((ghostRotation_y+1)%field_y)*field_x] == Cell.WALL){
                    return false;
                }
                ghost.setY((ghostRotation_y+1)%field_y);
            }
            case LEFT -> {
                if(field_[(ghostRotation_x+field_x -1)%field_x+ghostRotation_y*field_x] == Cell.WALL){
                    return false;
                }
                ghost.setX((ghostRotation_x+field_x -1)%field_x);
            }
            case RIGHT -> {
                if(field_[(ghostRotation_x+1)%field_x+ghostRotation_y*field_x] == Cell.WALL){
                    return false;
                }
                ghost.setX((ghostRotation_x+1)%field_x);
            }
        }
        return true;
    }

 */

}
