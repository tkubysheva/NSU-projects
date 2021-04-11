package sample;

import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.util.Map;

public class VisualOptions {
    public void showHelp() {
        Stage stageHelp = new Stage();
        TextArea aboutArea = new TextArea("""
                The goal of the game is to collect as many points 
                as possible without getting caught by ghosts.
                The Pacman is controlled by the keyboard arrows (up, down, right, left).
                If you want to pause, press the "P" key.
                Have fun!""");
        aboutArea.setPrefColumnCount(30);
        aboutArea.setPrefRowCount(6);
        aboutArea.setEditable(false);
        StackPane rootHelp = new StackPane(aboutArea);
        Scene sceneHelp = new Scene(rootHelp, 400, 110);
        stageHelp.setScene(sceneHelp);
        stageHelp.setResizable(false);
        stageHelp.setTitle("Help");
        stageHelp.show();
    }

    public void showAbout() {
        Stage stageAbout = new Stage();
        TextArea aboutArea = new TextArea("""
                Author's game "pakman"\s
                second-year student of FIT NSU Kubysheva Tatyana
                2021""");
        aboutArea.setPrefColumnCount(30);
        aboutArea.setPrefRowCount(3);
        aboutArea.setEditable(false);
        StackPane rootAbout = new StackPane(aboutArea);
        Scene sceneAbout = new Scene(rootAbout, 300, 75);
        stageAbout.setScene(sceneAbout);
        stageAbout.setResizable(false);
        stageAbout.setTitle("Info");
        stageAbout.show();

    }

    public void showTopScores(int n) {
        Stage stageScores = new Stage();
        TextArea topScoresArea = new TextArea();

        Map<String, Integer> topFiveGamer = Scores.getTopGamer(n);
        topScoresArea.setPrefColumnCount(30);
        topScoresArea.setPrefRowCount(6);
        StringBuilder text = new StringBuilder();
        for (String k : topFiveGamer.keySet()) {
            text.append(k).append(" : ").append(topFiveGamer.get(k).toString()).append('\n');
        }
        //System.out.println(text.toString());
        topScoresArea.setText(text.toString());
        topScoresArea.setEditable(false);
        float sceneSizeY = 500;
        float sceneSizeX = 500;
        StackPane rootScores = new StackPane(topScoresArea);
        Scene sceneScores = new Scene(rootScores, sceneSizeX, sceneSizeY);
        stageScores.setScene(sceneScores);
        stageScores.setTitle("Top Scores");
        stageScores.show();
    }
}
