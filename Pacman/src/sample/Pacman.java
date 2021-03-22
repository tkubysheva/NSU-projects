package sample;

import javafx.scene.image.Image;

import java.io.FileInputStream;

public class Pacman {
    private Image pacmanImageLeft;
    private Image pacmanImageRight;
    private Image pacmanImageUp;
    private Image pacmanImageDown;
    private Direction direction = Direction.STOP;
    private Direction nextDirection = Direction.STOP;

    public Pacman(){
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanD.png")) {
            pacmanImageDown = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanL.png")) {
            pacmanImageLeft = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanU.png")) {
            pacmanImageUp = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanR.png")) {
            pacmanImageRight = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
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

    public Image getPacmanImage(){
        switch (direction){
            case UP -> {
                return pacmanImageUp;
            }
            case DOWN -> {
                return pacmanImageDown;
            }
            case LEFT -> {
                return pacmanImageLeft;
            }
            case RIGHT -> {
                return pacmanImageRight;
            }
        }
        return pacmanImageRight;
    }

}
