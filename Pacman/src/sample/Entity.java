package sample;

import javafx.scene.image.Image;

public class Entity {
    protected Image image;
    protected Direction direction = Direction.STOP;
    protected Direction nextDirection = Direction.STOP;

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

    public Image getImage() {
        return image;
    }
}
