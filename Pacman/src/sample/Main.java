package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.InputStream;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("PACMAN");
        primaryStage.setResizable(false);
        primaryStage.setScene(new Scene(root, 500, 300));

        InputStream iconStream = getClass().getResourceAsStream("/images/splash screen.png");
        Image image = new Image(iconStream);
        primaryStage.getIcons().add(image);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
