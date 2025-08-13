import java.util.*;

class OpCode {
    String type; // IS, DL, AD
    int code;

    OpCode(String type, int code) {
        this.type = type;
        this.code = code;
    }
}

class Symbol {
    String name;
    int address;

    Symbol(String name, int address) {
        this.name = name;
        this.address = address;
    }
}

class Literal {
    String value;
    int address;

    Literal(String value, int address) {
        this.value = value;
        this.address = address;
    }
}

public class TwoPassAssembler {

    static Map<String, OpCode> OPTAB = new HashMap<>();
    static List<Symbol> SYMTAB = new ArrayList<>();
    static List<Literal> LITTAB = new ArrayList<>();
    static List<Integer> POOLTAB = new ArrayList<>();
    static List<String> IC = new ArrayList<>();

    static int LC = 0; // Location counter

    public static void main(String[] args) {
        //  Initialize OPTAB
        initOPTAB();

        // Sample assembly program
        String[] program = {
            "START 100",
            "MOVER AREG, ='5'",
            "ADD BREG, ONE",
            "LOOP SUB AREG, TWO",
            "BC GT, LOOP",
            "MOVEM AREG, RESULT",
            "RESULT DS 1",
            "ONE DC 1",
            "TWO DC 2",
            "END"
        };

        // Pass-I
        passOne(program);

        // Show intermediate code & tables
        System.out.println("Intermediate Code:");
        IC.forEach(System.out::println);

        System.out.println("\nSYMTAB:");
        for (int i = 0; i < SYMTAB.size(); i++)
            System.out.println((i + 1) + "\t" + SYMTAB.get(i).name + "\t" + SYMTAB.get(i).address);

        System.out.println("\nLITTAB:");
        for (int i = 0; i < LITTAB.size(); i++)
            System.out.println((i + 1) + "\t" + LITTAB.get(i).value + "\t" + LITTAB.get(i).address);

        System.out.println("\nPOOLTAB:");
        POOLTAB.forEach(System.out::println);

        //Pass-II
        System.out.println("\nMachine Code:");
        passTwo();
    }

    static void initOPTAB() {
        OPTAB.put("STOP", new OpCode("IS", 00));
        OPTAB.put("ADD", new OpCode("IS", 01));
        OPTAB.put("SUB", new OpCode("IS", 02));
        OPTAB.put("MOVER", new OpCode("IS", 04));
        OPTAB.put("MOVEM", new OpCode("IS", 05));
        OPTAB.put("COMP", new OpCode("IS", 06));
        OPTAB.put("BC", new OpCode("IS", 07));
        OPTAB.put("READ", new OpCode("IS", 09));
        OPTAB.put("PRINT", new OpCode("IS", 10));

        OPTAB.put("DC", new OpCode("DL", 01));
        OPTAB.put("DS", new OpCode("DL", 02));

        OPTAB.put("START", new OpCode("AD", 01));
        OPTAB.put("END", new OpCode("AD", 02));
        OPTAB.put("ORIGIN", new OpCode("AD", 03));
        OPTAB.put("EQU", new OpCode("AD", 04));
        OPTAB.put("LTORG", new OpCode("AD", 05));
    }

    static void passOne(String[] program) {
        LC = 0;
        POOLTAB.add(0); // First pool start

        for (String line : program) {
            String[] parts = line.split("[ ,]+");
            String label = null, opcode, op1 = null, op2 = null;

            if (OPTAB.containsKey(parts[0]) || parts[0].startsWith("=")) {
                opcode = parts[0];
            } else {
                label = parts[0];
                opcode = parts[1];
                if (!label.isEmpty()) addSymbol(label, LC);
                if (parts.length > 2) op1 = parts[2];
                if (parts.length > 3) op2 = parts[3];
            }

            if (label == null) {
                opcode = parts[0];
                if (parts.length > 1) op1 = parts[1];
                if (parts.length > 2) op2 = parts[2];
            }

            OpCode op = OPTAB.get(opcode);

            if (op.type.equals("AD")) {
                if (opcode.equals("START")) {
                    LC = Integer.parseInt(op1);
                    IC.add("(AD," + op.code + ") (C," + op1 + ")");
                }
                if (opcode.equals("END") || opcode.equals("LTORG")) {
                    handleLiterals();
                    IC.add("(AD," + op.code + ")");
                }
            } else if (op.type.equals("DL")) {
                if (opcode.equals("DC")) {
                    IC.add("(DL," + op.code + ") (C," + op1 + ")");
                    LC++;
                }
                if (opcode.equals("DS")) {
                    IC.add("(DL," + op.code + ") (C," + op1 + ")");
                    LC += Integer.parseInt(op1);
                }
            } else if (op.type.equals("IS")) {
                String regCode = getRegisterCode(op1);
                String operandCode = getOperandCode(op2);
                IC.add("(IS," + op.code + ") " + regCode + " " + operandCode);
                LC++;
            }
        }
    }

    static void handleLiterals() {
        for (int i = POOLTAB.get(POOLTAB.size() - 1); i < LITTAB.size(); i++) {
            LITTAB.get(i).address = LC;
            LC++;
        }
        POOLTAB.add(LITTAB.size());
    }

    static void addSymbol(String name, int addr) {
        for (Symbol s : SYMTAB) {
            if (s.name.equals(name)) {
                s.address = addr;
                return;
            }
        }
        SYMTAB.add(new Symbol(name, addr));
    }

    static String getRegisterCode(String reg) {
        if (reg == null) return "(0)";
        switch (reg) {
            case "AREG": return "(1)";
            case "BREG": return "(2)";
            case "CREG": return "(3)";
            case "DREG": return "(4)";
            default: return "(0)";
        }
    }

    static String getOperandCode(String op) {
        if (op == null) return "(0)";
        if (op.startsWith("=")) {
            for (int i = 0; i < LITTAB.size(); i++) {
                if (LITTAB.get(i).value.equals(op)) return "(L," + (i + 1) + ")";
            }
            LITTAB.add(new Literal(op, -1));
            return "(L," + LITTAB.size() + ")";
        } else {
            for (int i = 0; i < SYMTAB.size(); i++) {
                if (SYMTAB.get(i).name.equals(op)) return "(S," + (i + 1) + ")";
            }
            SYMTAB.add(new Symbol(op, -1));
            return "(S," + SYMTAB.size() + ")";
        }
    }

    static void passTwo() {
        for (String line : IC) {
            if (line.startsWith("(IS")) {
                String[] parts = line.replace("(", "").replace(")", "").split(" ");
                int opcode = Integer.parseInt(parts[0].split(",")[1]);
                int reg = Integer.parseInt(parts[1]);
                String opType = parts[2].split(",")[0];
                int index = Integer.parseInt(parts[2].split(",")[1]);

                int addr = 0;
                if (opType.equals("S")) addr = SYMTAB.get(index - 1).address;
                else if (opType.equals("L")) addr = LITTAB.get(index - 1).address;

                System.out.println(opcode + " " + reg + " " + addr);
            } else if (line.startsWith("(DL,01)")) {
                String val = line.substring(line.indexOf("(C,") + 3, line.indexOf(")"));
                System.out.println("00 0 " + val);
            }
        }
    }
}

