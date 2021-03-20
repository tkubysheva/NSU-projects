package sample;

import java.io.FileInputStream;

public class Field {
    private final int field_x = 27;
    private final int field_y = 26;
    private int pacmanRotation_x = 0;
    private int pacmanRotation_y = 0;
    private int countOfDots = 0;

    private byte field[] = new byte[field_x*field_y];
    public Field() {
        try (FileInputStream f = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\sample\\field.txt")) {
            byte[] objects = new byte[f.available()];
            f.read(objects, 0, f.available());
            int pacmanRotation = 0;
            int c = 0;
            boolean iSeeAPacman = false;
            for(byte a: objects){
                if(a == 'o'||a == 'p'||a=='w'||a == 'm') {
                    field[c] = a;
                    if(!iSeeAPacman) {
                        pacmanRotation++;
                    }
                    if (a == 'm') {
                        iSeeAPacman = true;
                    }
                    if (a == 'p') {
                        countOfDots++;
                    }
                    c++;
                }
            }
            pacmanRotation_x = pacmanRotation%field_x;
            pacmanRotation_y = pacmanRotation/field_x;
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

    public int getPacmanRotation_x() {
        return pacmanRotation_x;
    }
    public int getPacmanRotation_y() {
        return pacmanRotation_y;
    }

    public int getField_x() {
        return field_x;
    }

    public int getField_y() {
        return field_y;
    }
}
