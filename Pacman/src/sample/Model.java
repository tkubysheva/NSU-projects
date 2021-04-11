package sample;

public class Model {
    public Model(int level) {
        field = new Field(level, pacman, ghostA, ghostB, ghostC);
    }

    private final Pacman pacman = new Pacman();
    private final Ghost ghostA = new Ghost();
    private final Ghost ghostB = new Ghost();
    private final Ghost ghostC = new Ghost();

    private final Dot dot = new Dot();
    private Field field;

    public Cell[] getObjects() {
        return field.getObjects();
    }

    public Pacman getPacman() {
        return pacman;
    }

    public Ghost getPinkGhost() {
        return ghostA;
    }

    public Ghost getBlueGhost() {
        return ghostB;
    }

    public Ghost getYellowGhost() {
        return ghostC;
    }

    public int getCountOfDots() {
        return field.getCountOfDots();
    }

    public boolean pacmanEaten() {
        if ((pacman.getX() == ghostA.getX() && pacman.getY() == ghostA.getY()) ||
                (pacman.getX() == ghostB.getX() && pacman.getY() == ghostB.getY()) ||
                (pacman.getX() == ghostC.getX() && pacman.getY() == ghostC.getY())) {
            return pacman.pacmanEaten();
        }
        return false;
    }

    public boolean pacmanInvulnerable() {
        return pacman.isInvulnerable();
    }

    public void pacmanNotInvulnerable() {
        pacman.endInvulnerable();
    }

    public void moveEntity() {
        move(pacman);
        move(ghostA);
        move(ghostB);
        move(ghostC);
    }

    public int addScore() {
        if (field.isDotEaten()) {
            field.dotUneaten();
            return dot.getAddScore();
        }
        return 0;
    }

    private void move(Entity entity) {
        boolean checkMove;
        if (entity.getClass() == Pacman.class) {
            checkMove = field.checkMovePacman(entity);
        } else {
            checkMove = field.checkMoveGhost(entity);
        }
        if (checkMove) {
            entity.setDirection();
        }
        if (!field.move(entity)) {
            entity.setDirection();
        }

    }


}
