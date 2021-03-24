package sample;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;

import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

public class Controller {
    Field field = new Field();
    private final Entity pacman = new Pacman();
    private final Entity ghostA = new PinkGhost();

    private Visual visual;
    @FXML
    private Button startButton;
    @FXML
    private Button exitButton;



    public void closeWindow(Button b) {
        Stage stage_ = (Stage) b.getScene().getWindow();
        stage_.close();
    }

    private void randomDirection(Entity g){
        Random rand = new Random();
        switch (rand.nextInt(4)){
            case 0 -> g.setNextDirection(Direction.LEFT);
            case 1 -> g.setNextDirection(Direction.UP);
            case 2 -> g.setNextDirection(Direction.DOWN);
            case 3 -> g.setNextDirection(Direction.RIGHT);
        }

    }
    private void pacmanMove(){
        if(field.checkMovePacman(pacman.getNextDirection())){
            pacman.setDirection();
        }
        if(!field.movePacman(pacman.getDirection())){
            pacman.setDirection();
        }
    }
    private void ghostsMove(){
        if(field.checkMoveGhostA(ghostA.getNextDirection())){
            ghostA.setDirection();
            randomDirection(ghostA);
        }
        if(!field.moveGhostA(ghostA.getDirection())){
            ghostA.setDirection();
            randomDirection(ghostA);
        }
    }
    private long lastTimerCall;
    protected AnimationTimer at = new AnimationTimer() {
        @Override
        public void handle(long now) {
            long interval = 250_000_000L;
            if (now > lastTimerCall + interval) {
                pacmanMove();
                ghostsMove();
                if(field.pacmanEaten()){
                    endGame(false);
                }
                visual.repaint(field.getObjects(), pacman.getImage(), ghostA.getImage());
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
                endGame(true);
            }
        }
    };

    @FXML
    void initialize() {
        exitButton.setOnMouseClicked((event) -> closeWindow(exitButton));

        startButton.setOnMouseClicked((event) -> {
            closeWindow(startButton);
            visual = new Visual(field.getObjects(), pacman.getImage(), ghostA.getImage());
            startGame();
        });

    }
    private void endGame(boolean isWinner){
        pacman.setNextDirection(Direction.STOP);
        pacman.setDirection();
        visual.GameOver(isWinner);
        at.stop();
    }
    private void startGame() {
        at.start();
    }
}


