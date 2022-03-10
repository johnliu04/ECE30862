import java.util.*;
import java.io.*;
import java.io.IOException;

public class bytecode {
    public ArrayList<String> fileInput = new ArrayList<String>();
    public ArrayList<Integer> memory = new ArrayList<Integer>();
    public Map<String, Integer> symbolTable = new HashMap<>();
    public int pc = -1;
    public int offset = -1;

    public bytecode(BufferedReader bReader) throws IOException {
        ArrayList<String> command = new ArrayList<String>();
        String line;
        do {
            line = bReader.readLine();
            if (line != null)
                command.add(line);
        } while(line != null);
        fileInput = command;
    }

    void compile() throws IOException {
        int i = 0;
        for (String str : fileInput) {
            parse(str);
        }
        pc = -1;
        offset = -1;
        memory = new ArrayList<>();
        for (String str : fileInput) {
            parse(str);
        }
        try {
            DataOutputStream fileWriter = new DataOutputStream(new FileOutputStream("output"));
            for (int x : memory) {
                fileWriter.write(x);
            }
            fileWriter.close();
        } catch (FileNotFoundException e) {
            System.out.println("Output file not created.");
        }
    };

    public void parse(String command){
        if (command.isEmpty() || command.matches("(.*)//(.*)")) {
            return;
        }
        int index = 0;
        String[] tokens = command.split(" ");
        //System.out.println(tokens[0]);
        if (tokens[0].equals("decl")) {
            offset++;
            symbolTable.put(tokens[1], offset);
            pushi(0);
        }
        else if (tokens[0].equals("lab")) {
            symbolTable.put(tokens[1], pc + 1);
        }
        else if (tokens[0].equals("subr")) {
            pushi(16);
            pushi(17);
            pushi(1);
            memory.add(44);
            pc++;
            memory.add(0);
            pc++;
        }
        else if (tokens[0].equals("ret")) {
            pushi(0);
            memory.add(77);
            pc++;
            memory.add(48);
            pc++;;
        }
        else if (tokens[0].equals("printi")) {
            printi(Integer.parseInt(tokens[1]));
        }
        else if (tokens[0].equals("printv")) {
            index = symbolTable.get(tokens[1]);
            pushi(index);
            memory.add(74);
            pc++;
            memory.add(146);
            pc++;
        }
        else if (tokens[0].equals("jmp")) {
            if (symbolTable.containsKey(tokens[1])) {
                index = symbolTable.get(tokens[1]);
            }
            pushi(index);
            memory.add(36);
            pc++;
        }
        else if (tokens[0].equals("jmpc")) {
            if (symbolTable.containsKey(tokens[1])) {
                index = symbolTable.get(tokens[1]);
            }
            pushi(index);
            memory.add(40);
            pc++;
        }
        else if (tokens[0].equals("cmpe")) {
            memory.add(132);
            pc++;
        }
        else if (tokens[0].equals("cmplt")) {
            memory.add(136);
            pc++;
        }
        else if (tokens[0].equals("cmpgt")) {
            memory.add(140);
            pc++;
        }
        else if (tokens[0].equals("pushi")) {
            pushi(Integer.parseInt(tokens[1]));
        }
        else if (tokens[0].equals("pushv")) {
            index = symbolTable.get(tokens[1]);
            pushi(index);
            memory.add(74);
            pc++;
        }
        else if (tokens[0].equals("popm")) {
            pushi(Integer.parseInt(tokens[1]));
            memory.add(76);
        }
        else if (tokens[0].equals("popv")) {
            index = symbolTable.get(tokens[1]);
            pushi(index);
            memory.add(80);
            pc++;
        }
        else if (tokens[0].equals("peek")) {
            index = symbolTable.get(tokens[1]);
            pushi(index);
            pushi(Integer.parseInt(tokens[2]));
            memory.add(86);
            pc++;
        }
        else if (tokens[0].equals("poke")) {
            index = symbolTable.get(tokens[2]);
            pushi(index);
            pushi(Integer.parseInt(tokens[1]));
            memory.add(90);
            pc++;
        }
        else if (tokens[0].equals("swp")) {
            memory.add(94);
            pc++;
        }
        else if (tokens[0].equals("add")) {
            memory.add(100);
            pc++;
        }
        else if (tokens[0].equals("sub")) {
            memory.add(104);
            pc++;
        }
        else if (tokens[0].equals("mul")) {
            memory.add(108);
            pc++;
        }
        else if (tokens[0].equals("div")) {
            memory.add(112);
            pc++;
        }
        else {
            System.out.println("Invalid Command");
        }
    };

    public void printi(int num){
        // Convert num to bytes
        int[] num_bytes = {(num & 0x000000ff) >> 0, 
                           (num & 0x0000ff00) >> 8,
                           (num & 0x00ff0000) >> 16, 
                           (num & 0xff000000) >> 24};

        memory.add(70);
        pc++;
        for (int n = 0; n < 4; n++){
            memory.add(num_bytes[n]);
            pc++;
        }
        memory.add(146);
        pc++;
    };
    
    public void pushi(int num){
        // Convert num to bytes
        int[] num_bytes = {(num & 0x000000ff) >> 0, 
                           (num & 0x0000ff00) >> 8,
                           (num & 0x00ff0000) >> 16, 
                           (num & 0xff000000) >> 24};

        memory.add(70);
        pc++;
        for (int n = 0; n < 4; n++){
            memory.add(num_bytes[n]);
            pc++;
        }
    };

}
