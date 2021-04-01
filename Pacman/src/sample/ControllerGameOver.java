package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;


public class ControllerGameOver {

    public TextArea nameField;
    @FXML
    private Button nextGameButton;

    @FXML
    private Button exitGameButton;

    @FXML
    private Button repeatGameButton;
    @FXML
    private Button nameWrited;


    @FXML
    void initialize() {
        exitGameButton.setOnMouseClicked((event) -> {
            Stage s = (Stage) exitGameButton.getScene().getWindow();
            Stage owner =(Stage) s.getOwner();
            owner.close();
            Stage stage_ = (Stage) exitGameButton.getScene().getWindow();
            stage_.close();
        });
        repeatGameButton.setOnMouseClicked(event -> {
            ////////////
        });
        nameWrited.setOnMouseClicked(event ->{
            String name = nameField.getText();
            Scores.updateScore(name);
        });
    }
}
