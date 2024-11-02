import os

def find_next_test_number():
    """Find the next available test number by checking existing files."""
    i = 1
    while os.path.exists(f"teste{i}.in"):
        i += 1
    return i

def write_output(filename, lines):
    """Write output lines to a file."""
    with open(filename, 'w') as f:
        for line in lines:
            f.write(str(line) + '\n')

def generate_test_case(tad_type, set_a, set_b, operation, check_element=None):
    """Generate test case input and expected output."""
    test_number = find_next_test_number()
    input_filename = f"teste{test_number}.in"
    output_filename = f"teste{test_number}.out"
    
    # Generate input file
    with open(input_filename, 'w') as f:
        f.write(f"{tad_type}\n")
        f.write(f"{len(set_a)}\n")
        f.write(f"{len(set_b)}\n")
        
        for elem in set_a:
            f.write(f"{elem}\n")
            
        for elem in set_b:
            f.write(f"{elem}\n")
            
        f.write(f"{operation}\n")
        
        if operation == 1:
            f.write(f"{check_element}\n")
    
    # Generate output file
    output_lines = []
    
    if operation == 1:
        output_lines.append("Operação escolhida: PERTENCE")
        output_lines.append("Pertence." if check_element in set_a else "Nao pertence.")
    
    elif operation == 2:
        output_lines.append("Operação escolhida: UNIAO")
        union_result = sorted(list(set(set_a).union(set_b)))
        output_lines.append(' '.join(map(str, union_result)))
    
    elif operation == 3:
        output_lines.append("Operação escolhida: INTERSEC")
        intersec_result = sorted(list(set(set_a).intersection(set_b)))
        output_lines.append(' '.join(map(str, intersec_result)))
    
    write_output(output_filename, output_lines)
    
    # Print test case information
    print(f"\nTest case {test_number}:")
    print(f"Input file: {input_filename}")
    print(f"Output file: {output_filename}")
    print("Test description:", get_test_description(test_number))

def get_test_description(test_number):
    """Return description for each test case."""
    descriptions = {
        1: "Basic PERTENCE test with element present",
        2: "Basic PERTENCE test with element absent",
        3: "Basic UNIAO test with List",
        4: "Basic INTERSEC test with List",
        5: "Edge case: Very large numbers",
        6: "Edge case: Negative numbers",
        7: "Edge case: Duplicate elements",
        8: "Edge case: Empty set A",
        9: "Edge case: Empty set B",
        10: "Edge case: Single element sets",
        11: "Edge case: Maximum integer values",
        12: "Edge case: Mixed positive/negative numbers",
        13: "Edge case: Sequential numbers",
        14: "Edge case: Sparse numbers",
        15: "Edge case: All same numbers"
    }
    return descriptions.get(test_number, "Additional test case")

def main():
    # Basic test cases
    generate_test_case(
        tad_type=0,
        set_a=[1, 3, 5, 7, 9],
        set_b=[2, 4, 6, 8, 10],
        operation=1,
        check_element=5
    )
    
    generate_test_case(
        tad_type=0,
        set_a=[1, 3, 5, 7, 9],
        set_b=[2, 4, 6, 8, 10],
        operation=1,
        check_element=4
    )
    
    generate_test_case(
        tad_type=0,
        set_a=[1, 3, 5],
        set_b=[2, 3, 4],
        operation=2
    )
    
    generate_test_case(
        tad_type=0,
        set_a=[1, 2, 3, 4, 5],
        set_b=[3, 4, 5, 6, 7],
        operation=3
    )
    
    # Edge cases
    
    # Very large numbers
    generate_test_case(
        tad_type=1,
        set_a=[1000000, 999999, 999998],
        set_b=[999999, 999997, 1000000],
        operation=2
    )
    
    # Negative numbers
    generate_test_case(
        tad_type=1,
        set_a=[-5, -3, -1],
        set_b=[-4, -2, -1],
        operation=3
    )
    
    # Duplicate elements (should be handled by set operations)
    generate_test_case(
        tad_type=0,
        set_a=[1, 1, 2, 2, 3],
        set_b=[2, 2, 3, 3, 4],
        operation=2
    )
    
    # Empty set A
    generate_test_case(
        tad_type=0,
        set_a=[],
        set_b=[1, 2, 3],
        operation=2
    )
    
    # Empty set B
    generate_test_case(
        tad_type=1,
        set_a=[1, 2, 3],
        set_b=[],
        operation=3
    )
    
    # Single element sets
    generate_test_case(
        tad_type=0,
        set_a=[42],
        set_b=[42],
        operation=3
    )
    
    # Maximum integer values
    generate_test_case(
        tad_type=1,
        set_a=[2147483647, 2147483646],
        set_b=[2147483647, 2147483645],
        operation=2
    )
    
    # Mixed positive/negative
    generate_test_case(
        tad_type=0,
        set_a=[-100, -50, 0, 50, 100],
        set_b=[-75, -25, 0, 25, 75],
        operation=3
    )
    
    # Sequential numbers
    generate_test_case(
        tad_type=1,
        set_a=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
        set_b=[5, 6, 7, 8, 9, 10, 11, 12, 13, 14],
        operation=2
    )
    
    # Sparse numbers
    generate_test_case(
        tad_type=0,
        set_a=[1, 10, 100, 1000, 10000],
        set_b=[2, 20, 200, 2000, 20000],
        operation=2
    )
    
    # All same numbers
    generate_test_case(
        tad_type=1,
        set_a=[42, 42, 42, 42],
        set_b=[42, 42, 42],
        operation=3
    )

if __name__ == "__main__":
    main()