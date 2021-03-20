package sample;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

import java.io.FileInputStream;

public class Dot {
    private Image dotImage;
    private final int addScore = 10;

    public Dot() {
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\dot.png")) {
            dotImage = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public Image getDotImage() {
        return dotImage;
    }

    public void PrintDot(GraphicsContext gc, double x, double y, double dx, double dy){
        gc.drawImage(dotImage, x*dx + dx/3, y*dy +dy/3, dx/3, dy/3);
    }

    public int getAddScore() {
        return addScore;
    }
}
