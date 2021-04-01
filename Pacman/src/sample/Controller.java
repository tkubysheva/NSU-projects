package sample;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;

import java.awt.*;
import java.io.File;
import java.io.PrintStream;


public class Controller {
    private Visual visual;
    private final Model model = new Model();
    @FXML
    private Button startButton;
    @FXML
    private Button exitButton;
    @FXML
    private Button showResultsButton;


    public void closeWindow(Button b) {
        Stage stage_ = (Stage) b.getScene().getWindow();
        stage_.close();
    }

    private void onKeyPressed(){
        visual.getScene().setOnKeyPressed(keyEvent ->  {
            if(keyEvent.getCode() == KeyCode.DOWN){
                model.getPacman().setNextDirection(Direction.DOWN);
            }
            else if(keyEvent.getCode() == KeyCode.UP){
                model.getPacman().setNextDirection(Direction.UP);
            }
            else if(keyEvent.getCode() == KeyCode.RIGHT){
                model.getPacman().setNextDirection(Direction.RIGHT);
            }
            else if(keyEvent.getCode() == KeyCode.LEFT){
                model.getPacman().setNextDirection(Direction.LEFT);
            }
            else{
                System.out.println(keyEvent.getCode());
                System.out.println("I CAN'T MOVE((((((");
            }
        });
    }
    private long lastTimerCall;
    protected AnimationTimer at = new AnimationTimer() {
        @Override
        public void handle(long now) {
            if(model.pacmanEaten()){
                endGame(false);
            }
            long interval = 150_000_000L;
            if (now > lastTimerCall + interval) {
                model.moveEntity();
                Scores.setCurrentScore(model.addScore());
                visual.repaint(model.getObjects(), model.getPacman(), model.getPinkGhost(), model.getBlueGhost());
                lastTimerCall = now;
            }
            onKeyPressed();
            if(model.getCountOfDots() == 0){
                endGame(true);
            }
        }
    };

    @FXML
    void initialize() {
        exitButton.setOnMouseClicked((event) -> closeWindow(exitButton));

        startButton.setOnMouseClicked((event) -> {
            closeWindow(startButton);
            visual = new Visual(model.getObjects(), model.getPacman(), model.getPinkGhost(), model.getBlueGhost());
            startGame();
        });

        showResultsButton.setOnMouseClicked((event) -> {
            String resultsFilePath = "C:\\Users\\hp\\IdeaProjects\\pacman\\src\\sample\\results.txt";
            try (PrintStream output = new PrintStream(resultsFilePath)) {
                Scores.printScore(output);
                File f = new File(resultsFilePath);
                Desktop.getDesktop().open(f);
            }
            catch (Exception e){
                e.printStackTrace();
            }

            });
    }
    private void endGame(boolean isWinner){
        at.stop();
        visual.GameOver(isWinner);

    }
    private void startGame() {
        at.start();
    }
}


