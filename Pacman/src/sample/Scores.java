package sample;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.*;

public class Scores {
    private static final String propertyPath = "C:\\Users\\hp\\IdeaProjects\\pacman\\src\\sample\\scores.properties";
    private static final Properties scoreProp = new Properties();
    private static Integer currentScore = 0;

    public static void addCurrentScore(int score) {
        currentScore += score;
    }

    public static void resetScore() {
        currentScore = 0;
    }

    public Scores() {
        loadScore();
    }

    private static void loadScore() {
        try (FileInputStream fileInputStream = new FileInputStream(propertyPath)) {
            scoreProp.load(fileInputStream);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void storeScore() {
        try (FileOutputStream fileOutputStream = new FileOutputStream(propertyPath)) {
            scoreProp.store(fileOutputStream, null);
            //System.out.println(scoreProp);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void updateScore(String name) {
        loadScore();
        if (scoreProp.containsKey(name)) {
            int sc = Integer.parseInt(scoreProp.getProperty(name));
            if (sc >= currentScore) {
                return;
            }
        }
        //System.out.println("SET SCORE");
        String s = currentScore.toString();
        scoreProp.setProperty(name, s);
        storeScore();

    }

    public static Integer getCurrentScore() {
        return currentScore;
    }

    public static void printScore(PrintStream printStream) {
        loadScore();
        scoreProp.list(printStream);
    }

    public static Map<String, Integer> getTopGamer(int n) {
        loadScore();
        int index = 0, value = 0;
        ArrayList<String> keys = new ArrayList<>(n);
        ArrayList<Integer> values = new ArrayList<>(n);
        Map<String, Integer> hashMap = new HashMap<>();
        for (String key : scoreProp.stringPropertyNames()) {
            hashMap.put(key, Integer.parseInt(scoreProp.getProperty(key)));
        }
        for (String key : hashMap.keySet()) {
            value = hashMap.get(key);
            index = keys.size() - 1;
            while (index >= 0 && value > values.get(index)) {
                index--;
            }
            index = index + 1;
            values.add(index, value);
            keys.add(index, key);
            if (values.size() > n) {
                values.remove(n);
                keys.remove(n);
            }
        }
        Map<String, Integer> result = new HashMap<>(values.size());
        for (int i = 0; i < values.size(); i++) {
            result.put(keys.get(i), values.get(i));
        }
        return result;
    }

}
