//Design a Suitable Data Structure and Implement Pass 1 of a 2 Pass Macro Processor using OOP features in Java
import java.util.*;

// Entry in Macro Name Table (MNT)
class MNTEntry {
    String name;   
    int mdtIndex;  

    public MNTEntry(String name, int mdtIndex) {
        this.name = name;
        this.mdtIndex = mdtIndex;
    }
}

public class Pass1 {

    static class Pass1MacroProcessor {

        List<MNTEntry> MNT = new ArrayList<>();
        List<String> MDT = new ArrayList<>();
        List<String> intermediateCode = new ArrayList<>();

        public void process(String[] sourceCode) {
            boolean isMacroDef = false;

            for (int i = 0; i < sourceCode.length; i++) {
                String line = sourceCode[i].trim();

                if (line.equals("MACRO")) {
                    isMacroDef = true;

                    // Next line is macro header
                    String header = sourceCode[++i].trim();
                    String[] parts = header.split("\\s+");
                    String macroName = parts[0];

                    // Add macro to MNT
                    MNT.add(new MNTEntry(macroName, MDT.size() + 1));

                    // Replace parameters in MDT with positional notation
                    String[] params = Arrays.copyOfRange(parts, 1, parts.length);
                    Map<String, String> ala = new HashMap<>();
                    for (int p = 0; p < params.length; p++) {
                        ala.put(params[p], "#" + p);
                    }

                    // Process macro body until MEND
                    while (!sourceCode[++i].trim().equals("MEND")) {
                        String macroLine = sourceCode[i].trim();
                        for (Map.Entry<String, String> entry : ala.entrySet()) {
                            macroLine = macroLine.replace(entry.getKey(), entry.getValue());
                        }
                        MDT.add(macroLine);
                    }

                    MDT.add("MEND");
                    isMacroDef = false;
                }
                else if (!isMacroDef) {
                    // Intermediate Code
                    intermediateCode.add(line);
                }
            }
        }

        public void printTables() {
            System.out.println("MNT:");
            for (int i = 0; i < MNT.size(); i++) {
                MNTEntry entry = MNT.get(i);
                System.out.println((i + 1) + "\t" + entry.name + "\t" + entry.mdtIndex);
            }

            System.out.println("\nMDT:");
            for (int i = 0; i < MDT.size(); i++) {
                System.out.println((i + 1) + "\t" + MDT.get(i));
            }

            System.out.println("\nIntermediate Code:");
            for (String line : intermediateCode) {
                System.out.println(line);
            }
        }
    }

    public static void main(String[] args) {
        String[] program = {
            "MACRO",
            "INCR &X",
            "MOVER AREG,&X",
            "ADD AREG,ONE",
            "MOVEM AREG,&X",
            "MEND",
            "START 100",
            "READ ALPHA",
            "INCR ALPHA",
            "PRINT ALPHA",
            "END"
        };

        Pass1MacroProcessor pass1 = new Pass1MacroProcessor();
        pass1.process(program);
        pass1.printTables();
    }
}

