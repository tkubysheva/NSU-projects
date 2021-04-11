package sample;

public class Ghost extends Entity {
    public Ghost() {
        nextDirection = Direction.LEFT;
    }

    private boolean isExist = false;

    public boolean isExist() {
        return isExist;
    }

    public void setExist(boolean exist) {
        isExist = exist;
    }

    @Override
    public void setDirection() {
        super.setDirection();
        super.randomNextDirection();
    }
}
