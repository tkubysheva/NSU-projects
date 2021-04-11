package sample;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
<<<<<<< HEAD
import javafx.scene.control.ComboBox;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;

import java.util.concurrent.atomic.AtomicInteger;


public class Controller {
    private final int maxLevel = 7;
    private final int startUpdateSpeedLevel = 3;
    private final int stopUpdateSpeedLevel = 8;
    private final int countOfTopScores = 5;
    private int level = 0;
    private Visual visual;
    private final VisualOptions visualOptions = new VisualOptions();
    private Model model;
    private boolean isPause = false;
=======
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;

import java.awt.*;
import java.io.File;
import java.io.PrintStream;


public class Controller {
    private Visual visual;
    private final Model model = new Model();
>>>>>>> 12886ea2dfc140b3c48ff99b293f2ef44b0cce4a
    @FXML
    private Button startButton;
    @FXML
    private Button exitButton;
    @FXML
    private Button showResultsButton;
<<<<<<< HEAD
    @FXML
    private Button helpButton;
    @FXML
    private Button infoButton;
    @FXML
    private ComboBox chooseLevelBox;
=======

>>>>>>> 12886ea2dfc140b3c48ff99b293f2ef44b0cce4a

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
<<<<<<< HEAD
            else if(keyEvent.getCode() == KeyCode.P){
                isPause = true;
                visual.pause();
            }
=======
>>>>>>> 12886ea2dfc140b3c48ff99b293f2ef44b0cce4a
            else{
                System.out.println(keyEvent.getCode());
                System.out.println("I CAN'T MOVE((((((");
            }
        });
    }
<<<<<<< HEAD
    private long interval = 150_000_000L;
    private long lastTimerCall;
    private int counterInvulnerable = 0;
    protected AnimationTimer at = new AnimationTimer() {
        @Override
        public void handle(long now) {
            if(isPause){
                if(!visual.pauseIsShowing()){
                    isPause = false;
                }
                return;
            }
            int numberOfInvulnerableFrames = 15;

            if (now > lastTimerCall + interval) {
                if(model.pacmanInvulnerable() && counterInvulnerable == numberOfInvulnerableFrames){
                    model.pacmanNotInvulnerable();
                    counterInvulnerable = 0;
                }
                else if(model.pacmanInvulnerable()){
                    counterInvulnerable++;
                }
                if(model.pacmanEaten()){
                    endGame(false);
                }

                model.moveEntity();
                Scores.addCurrentScore(model.addScore());
                visual.repaint(model.getObjects(), model.getPacman(), model.getPinkGhost(),
                        model.getBlueGhost(), model.getYellowGhost());
=======
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
>>>>>>> 12886ea2dfc140b3c48ff99b293f2ef44b0cce4a
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
<<<<<<< HEAD
        AtomicInteger chosenLevel = new AtomicInteger();
        chooseLevelBox.getItems().removeAll(chooseLevelBox.getItems());
        chooseLevelBox.getItems().addAll("1", "2", "3", "4", "5", "6", "7", "8", "9", "10");
        //chooseLevelBox.getSelectionModel().select("1");

        chooseLevelBox.setOnAction(event -> {
            String i =chooseLevelBox.getValue().toString();
                chosenLevel.set(Integer.parseInt(i)  - 1);
        });

=======
>>>>>>> 12886ea2dfc140b3c48ff99b293f2ef44b0cce4a
        exitButton.setOnMouseClicked((event) -> closeWindow(exitButton));

        startButton.setOnMouseClicked((event) -> {
            closeWindow(startButton);
<<<<<<< HEAD
            while(level != chosenLevel.get()){
                levelUp();
            }
            startGame();
        });
        showResultsButton.setOnMouseClicked((event) -> {
            visualOptions.showTopScores(countOfTopScores);
            });
        infoButton.setOnMouseClicked(event -> {
            visualOptions.showAbout();
        });
        helpButton.setOnMouseClicked(event -> {
            visualOptions.showHelp();
        });

    }
    private void endGame(boolean isWinner){
        at.stop();
        visual.gameOver(isWinner, this);

    }
    public boolean levelUp(){
        level++;
        if(level == maxLevel){
            visual.gamePassed();
            return false;
        }
        if(level >= startUpdateSpeedLevel && level < stopUpdateSpeedLevel){
            interval -= 20_000_000L;
        }
        return true;
    }
    public void startGame() {
        model = new Model(level);
        visual = new Visual(model.getObjects(), model.getPacman(), model.getPinkGhost(), model.getBlueGhost(), model.getYellowGhost());
=======
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
>>>>>>> 12886ea2dfc140b3c48ff99b293f2ef44b0cce4a
        at.start();
    }
}


