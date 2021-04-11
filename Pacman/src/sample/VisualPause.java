package sample;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

public class VisualPause {
    private final Stage stagePause = new Stage();
    private boolean isShowing = false;

    public boolean isShowing() {
        return isShowing;
    }

    public VisualPause(Stage stage) {
        Button startButton = new Button("Return to the game");
        float sceneSizeY = 150;
        float sceneSizeX = 300;
        StackPane rootPause = new StackPane(startButton);
        Scene scenePause = new Scene(rootPause, sceneSizeX, sceneSizeY);
        stagePause.initModality(Modality.WINDOW_MODAL);
        stagePause.initOwner(stage);
        stagePause.setTitle("Pause");
        stagePause.setResizable(false);
        EventHandler<ActionEvent> event = new EventHandler<ActionEvent>() {
            public void handle(ActionEvent e) {
                stagePause.close();
                isShowing = false;
            }
        };
        stagePause.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent event) {
                event.consume();
            }
        });
        startButton.setOnAction(event);
        stagePause.setScene(scenePause);
    }

    public void show() {
        isShowing = true;
        stagePause.show();
    }
}
