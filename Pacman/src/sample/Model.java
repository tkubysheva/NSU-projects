package sample;

public class Model {
    private final Entity pacman = new Pacman();
    private final Entity ghostA = new PinkGhost();
    private final Entity ghostB = new BlueGhost();
    private final Dot dot = new Dot();
    private final Field field = new Field(pacman, ghostA, ghostB);
    public Cell[] getObjects(){
        return field.getObjects();
    }
    public Entity getPacman() {
        return pacman;
    }

    public Entity getPinkGhost() {
        return ghostA;
    }

    public Entity getBlueGhost() {
        return ghostB;
    }

    public int getCountOfDots(){
        return field.getCountOfDots();
    }

    public boolean pacmanEaten(){
        return (pacman.getX() == ghostA.getX() && pacman.getY() == ghostA.getY()) ||
                (pacman.getX() == ghostB.getX() && pacman.getY() == ghostB.getY());
    }

    public void moveEntity(){
        pacmanMove();
        ghostsMove();
    }
    public int addScore(){
        if(field.isDotEaten()){
            field.dotUneaten();
            return dot.getAddScore();
        }
        return 0;
    }

    private void pacmanMove(){
        if(field.checkMovePacman(pacman)){
            pacman.setDirection();
        }
        if(!field.move(pacman)){
            pacman.setDirection();
        }
    }
    private void ghostsMove(){
        if(field.checkMoveGhost(ghostA)){
            ghostA.setDirection();
            ghostA.randomNextDirection(ghostA);
        }
        if(!field.move(ghostA)){
            ghostA.setDirection();
            ghostA.randomNextDirection(ghostA);
        }
        if(field.checkMoveGhost(ghostB)){
            ghostB.setDirection();
            ghostB.randomNextDirection(ghostB);
        }
        if(!field.move(ghostB)){
            ghostB.setDirection();
            ghostB.randomNextDirection(ghostB);
        }
    }

}
