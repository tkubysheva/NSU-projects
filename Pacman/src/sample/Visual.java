package sample;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class Visual {

    private final EntityImage images = new EntityImage();
    Stage stage = new Stage();
    Scene scene;
    Group root = new Group();
    Canvas canvas = new Canvas(600, 600);
    GraphicsContext gc = canvas.getGraphicsContext2D();

    public Visual(Cell[] objects, Entity pacman, Entity ghostPink, Entity ghostBlue ) {
        stage.setTitle("PACMAN!!!");
        stage.getIcons().add(images.getSplashScreen());
        stage.setResizable(false);
        paintField(objects, pacman, ghostPink, ghostBlue);
        root.getChildren().add(canvas);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void GameOver(boolean isWinner) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("gameOver.fxml"));
            Scene sceneOver = new Scene(fxmlLoader.load(), 600, 500);
            sceneOver.setFill(Color.BLACK);
            Stage stageOver = new Stage();
            stageOver.initModality(Modality.WINDOW_MODAL);
            stageOver.initOwner(stage);
            if(isWinner) {
                stageOver.setTitle("YOU WIN!!!");
            }
            else{
                stageOver.setTitle("YOU LOSE(((");
            }
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

    public void repaint(Cell[] objects, Entity pacman, Entity ghostPink, Entity ghostBlue) {
        paintField(objects,  pacman,  ghostPink,  ghostBlue);
        stage.setScene(scene);
    }

    private void paintField(Cell[] objects, Entity pacman, Entity ghostPink, Entity ghostBlue) {
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, gc.getCanvas().getWidth(), gc.getCanvas().getHeight());
        double dx = gc.getCanvas().getWidth() / 27;
        double dy = gc.getCanvas().getHeight() / 28;
        int x = 0, y = 0;
        try {
            for (Cell p : objects) {
                if (p == Cell.WALL) {
                    gc.setFill(Color.BLUE);
                    gc.fillRect(x * dx, y * dy, dx, dy);
                    x++;
                }
                else if (p == Cell.GHOST_WALL) {
                    gc.setFill(Color.RED);
                    gc.fillRect(x * dx, y * dy, dx, dy);
                    x++;
                }else if (p == Cell.POINT) {
                    gc.drawImage(images.getDotImage(), x * dx + dx / 3, y * dy + dy / 3, dx / 3, dy / 3);
                    x++;
                } else if (p == Cell.EMPTINESS) {
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
        gc.drawImage(images.getPacmanImage(pacman.getDirection()), pacman.getX() * dx,
                pacman.getY() * dy, dx, dy);
        gc.drawImage(images.getGhostPinkImage(), ghostPink.getX() * dx,
                ghostPink.getY() * dy, dx, dy);
        gc.drawImage(images.getGhostBlueImage(), ghostBlue.getX() * dx,
                ghostBlue.getY() * dy, dx, dy);
    }
}
