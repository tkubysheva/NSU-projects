package sample;

import javafx.scene.image.Image;

import java.io.FileInputStream;

public class Pacman extends Entity {
    private Image pacmanImageLeft;
    private Image pacmanImageRight;
    private Image pacmanImageUp;
    private Image pacmanImageDown;

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

    @Override
    public Image getImage(){
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
