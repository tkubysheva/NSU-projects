import programContent.DIRECTION;
import programContent.Content;

import java.io.*;

/**
 * Class Interpreter for Befunge
 *
 * @autor - Tatyana Kubysheva
 */
public class Interpreter extends Content {
    /**
     * Constructor
     *
     * @throws Exception If Factory can't load a properties-file
     */
    public Interpreter() throws Exception {
    }

    /**
     * Class to a place in the Befunge program field
     */
    private class Pointer {
        Pointer() {
            x = 0;
            y = 0;
        }

        int x;
        int y;
        char element;

        /**
         * Function reads a new command or element from the field.
         */
        public void newElement() {
            point.element = field[point.y * field_x + point.x];
            act();
        }

        /**
         * Function checks if an element is a number or a character to be pushed onto the stack.
         * If it is then it prepared for it.
         */
        private void act() {
            if (Character.isDigit(point.element) || (Character.isLetter(point.element) && stringMode)) {
                inStack = point.element;
                point.element = 'i';
            }
        }
    }

    /**
     * An instance of the pointer class to a place in the Befunge program field
     *
     * @see Pointer
     */
    private final Pointer point = new Pointer();
    /**
     * Command building factory
     *
     * @see Factory
     */
    private final Factory<commands.Command> factory = new Factory<>("listOfCommands.properties");

    /**
     * Function that loads the field of the Befunge program
     *
     * @param dir - The path to the file with the text of the Befunge program
     */
    private void loadFile(String dir) {
        try (FileInputStream f = new FileInputStream(dir)) {
            byte[] buff = new byte[f.available()];
            f.read(buff, 0, f.available());
            f.close();
            int i = 0, j = 0;
            for (byte p : buff) {
                field[i * field_x + j] = (char) p;
                j++;
                if (p == '\n') {
                    i++;
                    j = 0;
                }
                if (j > field_x || i > field_y) {
                    throw new Exception("File is larger then needed");
                }
            }
        } catch (Exception error) {
            System.out.println(error.getMessage());
        }
    }

    /**
     * Function that launches the Interpreter
     *
     * @param dir - The path to the file with the text of the Befunge program
     */
    public void Go(String dir) {
        loadFile(dir);
        playField();
    }

    /**
     * Function that goes through the cells of the field of the Befunge program
     */
    private void playField() {
        try {
            while (direction != DIRECTION.END) {
                point.newElement();
                commands.Command c = factory.InputClass(point.element);
                c.execute(this);
                step();
            }
        } catch (Exception error) {
            System.out.println(error.getMessage());
        }
    }

    /**
     * Function that does step in the current direction
     */
    private void step() {
        switch (direction) {
            case UP -> point.y = (point.y + field_y - 1) % field_y;
            case RIGHT -> point.x = (point.x + field_x + 1) % field_x;
            case DOWN -> point.y = (point.y + field_y + 1) % field_y;
            case LEFT -> point.x = (point.x + field_x - 1) % field_x;
        }
    }
}