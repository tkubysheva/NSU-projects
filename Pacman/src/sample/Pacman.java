package sample;


public class Pacman extends Entity {
    private int countOfLife = 3;
    private boolean isInvulnerable = false;

    public void endInvulnerable() {
        isInvulnerable = false;
    }

    public boolean isInvulnerable() {
        return isInvulnerable;
    }

    public boolean pacmanEaten() {
        if (isInvulnerable) {
            return false;
        }
        countOfLife--;
        isInvulnerable = true;
        return (countOfLife == 0);
    }

    public boolean isAlive() {
        return (countOfLife != 0);
    }

    public int getCountOfLife() {
        return countOfLife;
    }
}
