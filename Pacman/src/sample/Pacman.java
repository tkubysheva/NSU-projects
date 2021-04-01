package sample;


public class Pacman extends Entity {
    private int countOfLife = 3;
    public boolean pacmanEaten(){
        countOfLife--;
        return (countOfLife == 0);
    }
    public int getCountOfLife() {
        return countOfLife;
    }
}
