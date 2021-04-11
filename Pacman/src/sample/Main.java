package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;
import java.io.InputStream;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage){
        try {
            Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
            primaryStage.setTitle("PACMAN");
            primaryStage.setResizable(false);
            primaryStage.setScene(new Scene(root, 500, 300));
            InputStream iconStream = getClass().getResourceAsStream("/images/splash screen.png");
            Image image = new Image(iconStream);
            primaryStage.getIcons().add(image);
            primaryStage.show();
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        launch(args);
    }
}
