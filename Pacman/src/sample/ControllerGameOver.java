package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

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
    private Label scoreLabel;

    private boolean isWinner;
    private Controller controller;

    public void setWinner(boolean w) {
        isWinner = w;
    }

    public void setController(Controller controller) {
        this.controller = controller;
    }

    @FXML
    void initialize() {
        scoreLabel.setText(Scores.getCurrentScore().toString());

        exitGameButton.setOnMouseClicked((event) -> {
            Scores.resetScore();
            Stage s = (Stage) exitGameButton.getScene().getWindow();
            Stage owner = (Stage) s.getOwner();
            owner.close();
            Stage stage_ = (Stage) exitGameButton.getScene().getWindow();
            stage_.close();
        });
        repeatGameButton.setOnMouseClicked(event -> {
            Scores.resetScore();
            Stage s = (Stage) repeatGameButton.getScene().getWindow();
            Stage owner = (Stage) s.getOwner();
            owner.close();
            Controller c = new Controller();
            c.startGame();
        });
        nameWrited.setOnMouseClicked(event -> {
            String name = nameField.getText();
            Scores.updateScore(name);
        });
        nextGameButton.setOnMouseClicked(event -> {
            if (isWinner) {
                Stage s = (Stage) repeatGameButton.getScene().getWindow();
                Stage owner = (Stage) s.getOwner();
                owner.close();
                if (controller.levelUp()) {
                    controller.startGame();
                }
                /*
                Controller c = new Controller();
                if(c.levelUp()){
                    c.startGame();
                }

                 */
            }
        });
    }
}
