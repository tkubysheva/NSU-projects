package sample;

import javafx.scene.image.Image;

import java.util.Random;

public class Entity {
    public static class Point{
        protected int x;
        protected int y;
    }
    protected Point point = new Point();
    protected Direction direction = Direction.STOP;
    protected Direction nextDirection = Direction.STOP;

    public Point getPoint() {
        return point;
    }

    public int getX() {
        return point.x;
    }

    public int getY() {
        return point.y;
    }

    public void setX(int x) {
        this.point.x = x;
    }

    public void setY(int y) {
        this.point.y = y;
    }

    public Direction getNextDirection() {
        return nextDirection;
    }

    public void setNextDirection(Direction nextDirection) {
        this.nextDirection = nextDirection;
    }

    public void setDirection() {
        this.direction = this.nextDirection;
    }

    public Direction getDirection() {
        return direction;
    }

    public void randomNextDirection(Entity g){
        Random rand = new Random();
        switch (rand.nextInt(4)){
            case 0 -> g.setNextDirection(Direction.LEFT);
            case 1 -> g.setNextDirection(Direction.UP);
            case 2 -> g.setNextDirection(Direction.DOWN);
            case 3 -> g.setNextDirection(Direction.RIGHT);
        }

    }
}
