package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;


public class ControllerGameOver {
    @FXML
    private Button nextGameButton;

    @FXML
    private Button exitGameButton;

    @FXML
    private Button repeatGameButton;

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
            /*
            closeWindow(repeatGameButton);
            field.resetField();
            startGame();

             */
        });
    }
}
