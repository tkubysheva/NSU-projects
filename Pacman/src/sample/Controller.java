package sample;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;

public class Controller {
    Field field = new Field();
    private final Pacman pacman = new Pacman();
    private Visual visual;
    @FXML
    private Button startButton;
    @FXML
    private Button exitButton;



    public void closeWindow(Button b) {
        Stage stage_ = (Stage) b.getScene().getWindow();
        stage_.close();
    }

    private long lastTimerCall;
    protected AnimationTimer at = new AnimationTimer() {
        @Override
        public void handle(long now) {
            long interval = 250_000_000L;
            if (now > lastTimerCall + interval) {
                //System.out.println("I CAN REPAINT!!!");
                if(field.checkMove(pacman.getNextDirection())){
                    pacman.setDirection();
                }
                if(!field.movePacman(pacman.getDirection())){
                    pacman.setDirection();
                }
                visual.repaint(field.getObjects(), pacman.getPacmanImage());
                lastTimerCall = now;
            }
            visual.getScene().setOnKeyPressed(keyEvent ->  {
                if(keyEvent.getCode() == KeyCode.DOWN){
                    pacman.setNextDirection(Direction.DOWN);
                }
                else if(keyEvent.getCode() == KeyCode.UP){
                    pacman.setNextDirection(Direction.UP);
                }
                else if(keyEvent.getCode() == KeyCode.RIGHT){
                    pacman.setNextDirection(Direction.RIGHT);
                }
                else if(keyEvent.getCode() == KeyCode.LEFT){
                    pacman.setNextDirection(Direction.LEFT);
                }
                else{
                    System.out.println(keyEvent.getCode());
                    System.out.println("I CAN'T MOVE((((((");
                }
                });
            if(field.getCountOfDots() == 0){
                pacman.setNextDirection(Direction.STOP);
                pacman.setDirection();
                visual.GameOver();
                at.stop();
            }
        }
    };

    @FXML
    void initialize() {
        exitButton.setOnMouseClicked((event) -> closeWindow(exitButton));

        startButton.setOnMouseClicked((event) -> {
            closeWindow(startButton);
            visual = new Visual(field.getObjects(), pacman.getPacmanImage());
            startGame();
        });

    }
    private void startGame() {
        at.start();
    }
}


