package sample;

import java.io.FileInputStream;

public class Field {
    private final int field_x = 27;
    private final int field_y = 26;
    private int pacmanRotation_x = 0;
    private int pacmanRotation_y = 0;
    private int ghostARotation_x = 0;
    private int ghostARotation_y = 0;
    private byte ghostACell = 'o';
    private int countOfDots = 0;

    private byte field[] = new byte[field_x*field_y];
    public Field() {
        resetField();
    }
    public void resetField(){
        try (FileInputStream f = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\sample\\field.txt")) {
            byte[] objects = new byte[f.available()];
            f.read(objects, 0, f.available());
            int pacmanRotation = 0;
            int ghostARotation = 0;
            int c = 0;
            boolean iSeeAPacman = false;
            boolean iSeeAGhostA = false;
            for(byte a: objects){
                if(a == 'o'||a == 'p'||a=='w'||a == 'm' || a == 'W' || a == 'A') {
                    field[c] = a;
                    if(!iSeeAPacman) {
                        pacmanRotation++;
                    }
                    if(!iSeeAGhostA) {
                        ghostARotation++;
                    }
                    if (a == 'm') {
                        iSeeAPacman = true;
                    }
                    if (a == 'A') {
                        iSeeAGhostA = true;
                    }
                    if (a == 'p') {
                        countOfDots++;
                    }
                    c++;
                }
            }
            pacmanRotation_x = pacmanRotation%field_x - 1;
            pacmanRotation_y = pacmanRotation/field_x;

            ghostARotation_x = ghostARotation%field_x - 1;
            ghostARotation_y = ghostARotation/field_x;
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public int getCountOfDots(){
        return countOfDots;
    }
    public byte[] getObjects() {
        return field;
    }

    public boolean checkMovePacman(Direction d){
        switch (d){
            case UP -> {
                byte b = field[pacmanRotation_x+((pacmanRotation_y+field_y-1)%field_y)*field_x];
                if(b != 'w' && b != 'W'){
                    return true;
                }
            }
            case DOWN -> {
                byte b = field[pacmanRotation_x+((pacmanRotation_y+1)%field_y)*field_x];
                if(b!= 'w'&& b != 'W'){
                    return true;
                }
            }
            case LEFT -> {
                byte b = field[(pacmanRotation_x+field_x -1)%field_x+pacmanRotation_y*field_x];
                if(b != 'w'&& b != 'W'){
                    return true;
                }
            }
            case RIGHT -> {
                byte b = field[(pacmanRotation_x+1)%field_x+pacmanRotation_y*field_x];
                if( b!= 'w'&& b != 'W'){
                    return true;
                }
            }
        }
        return false;
    }

    public boolean movePacman(Direction d){
        switch (d){
            case UP -> {
                if(field[pacmanRotation_x+((pacmanRotation_y+field_y-1)%field_y)*field_x] == 'w'){
                    return false;
                }
                field[pacmanRotation_x+pacmanRotation_y*field_x] = 'o';
                pacmanRotation_y = (pacmanRotation_y+field_y-1)%field_y;

            }
            case DOWN -> {
                if(field[pacmanRotation_x+((pacmanRotation_y+1)%field_y)*field_x] == 'w'){
                    return false;
                }
                field[pacmanRotation_x+pacmanRotation_y*field_x] = 'o';
                pacmanRotation_y = (pacmanRotation_y+1)%field_y;
            }
            case LEFT -> {
                if(field[(pacmanRotation_x+field_x -1)%field_x+pacmanRotation_y*field_x] == 'w'){
                    return false;
                }
                field[pacmanRotation_x+pacmanRotation_y*field_x] = 'o';
                pacmanRotation_x = (pacmanRotation_x+field_x -1)%field_x;
            }
            case RIGHT -> {
                if(field[(pacmanRotation_x+1)%field_x+pacmanRotation_y*field_x] == 'w'){
                    return false;
                }
                field[pacmanRotation_x+pacmanRotation_y*field_x] = 'o';
                pacmanRotation_x = (pacmanRotation_x+1)%field_x;
            }
        }
        if(field[pacmanRotation_x+pacmanRotation_y*field_x] == 'p'){
            countOfDots--;
        }
        field[pacmanRotation_x+pacmanRotation_y*field_x] = 'm';
        return true;
    }
    public boolean checkMoveGhostA(Direction d){
        switch (d){
            case UP -> {
                if(field[ghostARotation_x+((ghostARotation_y+field_y-1)%field_y)*field_x] != 'w'){
                    return true;
                }
            }
            case DOWN -> {
                if(field[ghostARotation_x+((ghostARotation_y+1)%field_y)*field_x] != 'w'){
                    return true;
                }
            }
            case LEFT -> {
                if(field[(ghostARotation_x+field_x -1)%field_x+ghostARotation_y*field_x] != 'w'){
                    return true;
                }
            }
            case RIGHT -> {
                if(field[(ghostARotation_x+1)%field_x+ghostARotation_y*field_x] != 'w'){
                    return true;
                }
            }
        }
        return false;
    }

    public boolean moveGhostA(Direction d){
        switch (d){
            case UP -> {
                if(field[ghostARotation_x+((ghostARotation_y+field_y-1)%field_y)*field_x] == 'w'){
                    return false;
                }
                field[ghostARotation_x+ghostARotation_y*field_x] = ghostACell;
                ghostARotation_y = (ghostARotation_y+field_y-1)%field_y;

            }
            case DOWN -> {
                if(field[ghostARotation_x+((ghostARotation_y+1)%field_y)*field_x] == 'w'){
                    return false;
                }
                field[ghostARotation_x+ghostARotation_y*field_x] = ghostACell;
                ghostARotation_y = (ghostARotation_y+1)%field_y;
            }
            case LEFT -> {
                if(field[(ghostARotation_x+field_x -1)%field_x+ghostARotation_y*field_x] == 'w'){
                    return false;
                }
                field[ghostARotation_x+ghostARotation_y*field_x] = ghostACell;
                ghostARotation_x = (ghostARotation_x+field_x -1)%field_x;
            }
            case RIGHT -> {
                if(field[(ghostARotation_x+1)%field_x+ghostARotation_y*field_x] == 'w'){
                    return false;
                }
                field[ghostARotation_x+ghostARotation_y*field_x] = ghostACell;
                ghostARotation_x = (ghostARotation_x+1)%field_x;
            }
        }
        if(field[ghostARotation_x+ghostARotation_y*field_x] != 'A') {
            ghostACell = field[ghostARotation_x + ghostARotation_y * field_x];
        }
        field[ghostARotation_x+ghostARotation_y*field_x] = 'A';
        return true;
    }
    public boolean pacmanEaten(){
        return ghostACell == 'm';
    }
}
