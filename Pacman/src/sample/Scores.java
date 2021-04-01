package sample;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Properties;

public class Scores {
    private static final String propertyPath = "C:\\Users\\hp\\IdeaProjects\\pacman\\src\\sample\\scores.properties";
    private static final Properties scoreProp = new Properties();
    private static Integer currentScore = 0;

    public static void setCurrentScore(int score){
        currentScore += score;
    }

    public Scores() {
        loadScore();
    }
    private static void loadScore(){
        try(FileInputStream fileInputStream = new FileInputStream(propertyPath)){
            scoreProp.load(fileInputStream);
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
    private static void storeScore(){
        try(FileOutputStream fileOutputStream = new FileOutputStream(propertyPath)){
            scoreProp.store(fileOutputStream, null);
            System.out.println(scoreProp);
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void updateScore(String name){
        if(Integer.parseInt(scoreProp.getProperty(name)) < currentScore){
            String s = currentScore.toString();
            scoreProp.setProperty(name, s);
            storeScore();
        }
        currentScore = 0;
    }
    public static void printScore(PrintStream printStream){
        loadScore();
        scoreProp.list(printStream);
    }

}
