package sample;

import javafx.scene.image.Image;

import java.io.FileInputStream;

public class EntityImage {
    private Image splashScreen;
    private Image pacmanImageLeft;
    private Image pacmanImageRight;
    private Image pacmanImageUp;
    private Image pacmanImageDown;
    private Image pacmanImageClose;
    private boolean pacmanClose = false;
    private Image dotImage;
    private Image ghostPinkImage;
    private Image ghostBlueImage;
    private Image ghostYellowImage;
    private Image invulnerableImage;

    public EntityImage() {
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\splash screen.png")) {
            splashScreen = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanC.png")) {
            pacmanImageClose = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanD.png")) {
            pacmanImageDown = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanL.png")) {
            pacmanImageLeft = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanU.png")) {
            pacmanImageUp = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\pacmanR.png")) {
            pacmanImageRight = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\dot.png")) {
            dotImage = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\ghost1.png")) {
            ghostPinkImage = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\ghost3.png")) {
            ghostBlueImage = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\ghost2.png")) {
            ghostYellowImage = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        try (FileInputStream inputstream = new FileInputStream("C:\\Users\\hp\\IdeaProjects\\pacman\\src\\images\\red.png")) {
            invulnerableImage = new Image(inputstream);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public Image getGhostBlueImage() {
        return ghostBlueImage;
    }

    public Image getSplashScreen() {
        return splashScreen;
    }

    public Image getDotImage() {
        return dotImage;
    }

    public Image getGhostPinkImage() {
        return ghostPinkImage;
    }

    public Image getPacmanImage(Direction direction) {
        pacmanClose = !pacmanClose;
        if (pacmanClose) {
            return pacmanImageClose;
        }
        switch (direction) {
            case UP -> {
                return pacmanImageUp;
            }
            case DOWN -> {
                return pacmanImageDown;
            }
            case LEFT -> {
                return pacmanImageLeft;
            }
            case RIGHT -> {
                return pacmanImageRight;
            }
        }
        return pacmanImageRight;
    }

    public Image getInvulnerableImage() {
        return invulnerableImage;
    }

    public Image getGhostYellowImage() {
        return ghostYellowImage;
    }
}
