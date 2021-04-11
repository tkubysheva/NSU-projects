package sample;

import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;


public class Visual {

    private final EntityImage images = new EntityImage();
    Stage stage = new Stage();
    Scene scene;
    Group root = new Group();
    Canvas canvas = new Canvas(600, 600);
    GraphicsContext gc = canvas.getGraphicsContext2D();
    Label scoreLabel = new Label("Score: ");
    Label lifeLabel = new Label("Life: ");
    private final VisualPause visualPause = new VisualPause(stage);

    public Visual(Cell[] objects, Pacman pacman, Ghost ghostPink, Ghost ghostBlue, Ghost ghostYellow) {
        stage.setTitle("PACMAN!!!");
        stage.getIcons().add(images.getSplashScreen());
        stage.setResizable(false);
        paintField(objects, pacman, ghostPink, ghostBlue, ghostYellow);
        root.getChildren().add(canvas);
        scoreLabel.setLayoutY(600.0 * 26 / 28);
        scoreLabel.setTextFill(Color.YELLOW);
        lifeLabel.setLayoutY(600.0 * 26 / 28);
        lifeLabel.setLayoutX(600.0 / 3);
        lifeLabel.setTextFill(Color.YELLOW);
        root.getChildren().add(scoreLabel);
        root.getChildren().add(lifeLabel);
        scene = new Scene(root);
        stage.setScene(scene);
        stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent event) {
                Scores.resetScore();
            }
        });
        stage.show();
    }

    public boolean pauseIsShowing() {
        return visualPause.isShowing();
    }

    public void pause() {
        visualPause.show();
    }


    public void gameOver(boolean isWinner, Controller controller) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("gameOver.fxml"));

            Scene sceneOver = new Scene(fxmlLoader.load(), 600, 500, Color.BLACK);
            Stage stageOver = new Stage();
            stageOver.initModality(Modality.WINDOW_MODAL);
            stageOver.initOwner(stage);
            ControllerGameOver controllerGameOver = fxmlLoader.getController();
            controllerGameOver.setWinner(isWinner);
            controllerGameOver.setController(controller);
            if (isWinner) {
                stageOver.setTitle("YOU WIN!!!");
            } else {
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

    public void repaint(Cell[] objects, Pacman pacman, Ghost ghostPink, Ghost ghostBlue, Ghost ghostYellow) {
        paintField(objects, pacman, ghostPink, ghostBlue, ghostYellow);
        scoreLabel.setText("Score: " + Scores.getCurrentScore());
        lifeLabel.setText("Life: " + pacman.getCountOfLife());
        stage.setScene(scene);
    }

    private void paintField(Cell[] objects, Pacman pacman, Ghost ghostPink, Ghost ghostBlue, Ghost ghostYellow) {
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
                } else if (p == Cell.GHOST_WALL) {
                    gc.setFill(Color.RED);
                    gc.fillRect(x * dx, y * dy, dx, dy);
                    x++;
                } else if (p == Cell.POINT) {
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
        if (pacman.isInvulnerable()) {
            gc.drawImage(images.getInvulnerableImage(), pacman.getX() * dx,
                    pacman.getY() * dy, dx, dy);
        }
        if (ghostPink.isExist()) {
            gc.drawImage(images.getGhostPinkImage(), ghostPink.getX() * dx,
                    ghostPink.getY() * dy, dx, dy);
        }
        if (ghostBlue.isExist()) {
            gc.drawImage(images.getGhostBlueImage(), ghostBlue.getX() * dx,
                    ghostBlue.getY() * dy, dx, dy);
        }
        if (ghostYellow.isExist()) {
            gc.drawImage(images.getGhostYellowImage(), ghostYellow.getX() * dx,
                    ghostYellow.getY() * dy, dx, dy);
        }

    }

    public void gamePassed() {
        Stage stageAbout = new Stage();
        TextArea aboutArea = new TextArea("""
                Congratulations!
                You passed my first game!
                You are cool :)""");
        aboutArea.setPrefColumnCount(30);
        aboutArea.setPrefRowCount(3);
        aboutArea.setEditable(false);
        StackPane rootAbout = new StackPane(aboutArea);
        Scene sceneAbout = new Scene(rootAbout, 300, 75);
        stageAbout.setScene(sceneAbout);
        stageAbout.setResizable(false);
        stageAbout.setTitle("Game Over");
        stageAbout.show();
    }
}
