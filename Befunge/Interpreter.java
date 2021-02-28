import programContent.DIR;
import programContent.Content;

import java.io.*;


public class Interpreter {
    private class Pointer {
        Pointer() {
            x = 0;
            y = 0;
        }
        int x;
        int y;
        char element;
    }

    private Content program_content;
    private Pointer point;
    private final int field_x;
    private final int field_y;

    Interpreter() {
        field_x = 80;
        field_y = 25;
        program_content = new Content(field_x, field_y);
        point = new Pointer();

    }

    public void LoadFile(String dir) throws IOException {
        try (FileInputStream f = new FileInputStream(dir)) {
            byte[] buff = new byte[f.available()];
            f.read(buff, 0, f.available());
            f.close();
            int i = 0, j = 0;
            for (byte p : buff) {
                program_content.field[i * field_x + j] = (char) p;
                j++;
                if (p == '\n') {
                    i++;
                    j = 0;
                }
                if (j >= field_x || i > field_y) {
                    throw new IOException("File is larger then needed");
                }
            }
        } catch (IOException error) {
            System.out.println(error.getMessage());
        }
    }

    public void PlayField() throws Exception {
        point.element = program_content.field[point.y * field_x + point.x];
        while (program_content.direction != DIR.END) {
            if(point.element != ' ') {
                if (!program_content.bridge) {
                    Act();
                } else {
                    program_content.bridge = false;
                }
            }
            Step();
            point.element = program_content.field[point.y * field_x + point.x];
        }
    }

    private void Act() throws Exception {
        if(Character.isDigit(point.element) || (Character.isLetter(point.element) && program_content.stringMode)){
            program_content.inStack = point.element;
            point.element = 'i';
        }
        Reflection.Act(program_content, point.element);
    }

    private void Step() {
        switch (program_content.direction) {
            case UP -> point.y = (point.y + field_y - 1) % field_y;
            case RIGHT -> point.x = (point.x + field_x + 1) % field_x;
            case DOWN -> point.y = (point.y + field_y + 1) % field_y;
            case LEFT -> point.x = (point.x + field_x - 1) % field_x;
        }
    }
}

//библиотека lock for G