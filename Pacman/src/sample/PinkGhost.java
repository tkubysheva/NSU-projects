package sample;

import javafx.scene.image.Image;

import java.io.FileInputStream;

public class PinkGhost extends Entity{
    public PinkGhost(){
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\ghost1.png")) {
            image = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        nextDirection = Direction.UP;
    }
}
