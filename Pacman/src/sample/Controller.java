package sample;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class Controller {
    Field field = new Field();
    private final Pacman pacman = new Pacman(field.getPacmanRotation_x(),field.getPacmanRotation_y());
    int countDot= field.getCountOfDots();
    private Visual visual;
    @FXML
    private Button startButton;
    @FXML
    private Button exitButton;

    private void closeMenu(Button b) {
        Stage stage_ = (Stage) b.getScene().getWindow();
        stage_.close();
    }

    private long lastTimerCall;
    protected AnimationTimer at = new AnimationTimer() {
        @Override
        public void handle(long now) {
            long interval = 500_000_000L;
            if (now > lastTimerCall + interval) {
                //System.out.println("I CAN REPAINT!!!");
                if(!field.movePacman(pacman.getDirection())){
                    pacman.setDirection();
                }
                visual.repaint(field.getObjects(), pacman.getPacmanImage());
                lastTimerCall = now;
            }
            visual.getScene().setOnKeyTyped(keyEvent ->  {
                System.out.println("I CAN MOVE!!!");
                    switch (keyEvent.getCode()) {
                        case W -> pacman.setNextDirection(Direction.UP);
                        case S -> pacman.setNextDirection(Direction.DOWN);
                        case A -> pacman.setNextDirection(Direction.RIGHT);
                        case D -> pacman.setNextDirection(Direction.LEFT);
                    }
                });
            if(countDot == 0){
                visual.GameOver();
                at.stop();
            }
        }
    };

    @FXML
    void initialize() {
        exitButton.setOnMouseClicked((event) -> closeMenu(exitButton));

        startButton.setOnMouseClicked((event) -> {
            closeMenu(startButton);
            visual = new Visual(field.getObjects(), pacman.getPacmanImage());
            startGame();
        });


    }

    private void startGame() {
        at.start();
    }
}


