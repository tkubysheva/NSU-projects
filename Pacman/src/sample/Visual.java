package sample;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.paint.Color;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.FileInputStream;
import java.io.InputStream;

public class Visual {

    private final Dot dot = new Dot();
    Stage stage = new Stage();
    Scene scene;
    Group root = new Group();
    Canvas canvas = new Canvas(600, 600);
    GraphicsContext gc = canvas.getGraphicsContext2D();

    public Visual(byte objects[], Image pacmanImage) {
        stage.setTitle("PACMAN!!!");
        InputStream iconStream = getClass().getResourceAsStream("/images/splash screen.png");
        Image image = new Image(iconStream);
        stage.getIcons().add(image);
        stage.setResizable(false);
        paintField(objects, pacmanImage);
        root.getChildren().add(canvas);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void GameOver() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("gameOver.fxml"));
            Scene sceneOver = new Scene(fxmlLoader.load(), 600, 400);
            sceneOver.setFill(Color.BLACK);
            Stage stageOver = new Stage();
            stageOver.initModality(Modality.WINDOW_MODAL);
            stageOver.initOwner(stage);
            stageOver.setTitle("New Window");
            stageOver.setScene(sceneOver);
            stageOver.show();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public Scene getScene() {
        return scene;
    }

    public Stage getStage() {
        return stage;
    }

    public void repaint(byte[] objects, Image pacmanImage) {
        paintField(objects, pacmanImage);
        stage.setScene(scene);
    }

    private void paintField(byte[] objects, Image pacmanImage) {
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, gc.getCanvas().getWidth(), gc.getCanvas().getHeight());
        double dx = gc.getCanvas().getWidth() / 27;
        double dy = gc.getCanvas().getHeight() / 26;
        int x = 0, y = 0;
        try {
            for (byte p : objects) {
                if (p == 'w') {
                    gc.setFill(Color.BLUE);
                    gc.fillRect(x * dx, y * dy, dx, dy);
                    x++;
                } else if (p == 'p') {
                    gc.drawImage(dot.getDotImage(), x * dx + dx / 3, y * dy + dy / 3, dx / 3, dy / 3);
                    x++;
                } else if (p == 'o') {
                    x++;
                } else if (p == 'm') {
                    gc.drawImage(pacmanImage, x * dx, y * dy, dx, dy);
                    x++;
                }
                if (x == 27) {
                    x = 0;
                    y++;
                }
            }
        } catch (Exception error) {
            error.printStackTrace();
        }
    }
}
