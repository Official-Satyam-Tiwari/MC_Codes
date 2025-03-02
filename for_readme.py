
### Automatic README Generation:

import os

def get_project_info():
    # Get the repository name
    repo_name = os.path.basename(os.getcwd())

    # List of all files in the repo
    files = []
    for root, dirs, filenames in os.walk("."):
        for filename in filenames:
            files.append(os.path.join(root, filename))

    return repo_name, files

def generate_readme():
    repo_name, files = get_project_info()

    readme_content = f"# {repo_name}\n\n"
    readme_content += "Monte Carlo Codes\n\n"
    readme_content += "## Files and Directory Structure\n\n"
    
    # Create a directory structure similar to what we showed above
    directory_structure = "```plaintext\n"
    for file in files:
        directory_structure += file.replace(os.getcwd(), "").replace("\\", "/") + "\n"
    directory_structure += "```"

    readme_content += directory_structure
    readme_content += "\n\n## Code Overview\n\n"
    
    # Manually add descriptions for each section or use a similar approach as described earlier
    readme_content += "### 1. **3D_Geometry**\nContains code for simulations involving 3D geometric shapes, including basic and complex geometries.\n\n"
    readme_content += "### 2. **For Fun**\nIncludes fun problems like the Birthday Paradox, Monte Hall Problem, and Optimal Best Candidate simulations.\n\n"
    readme_content += "### 3. **Klein Nishijna**\nContains code related to the Klein-Nishina formula and its applications in Monte Carlo simulations.\n\n"
    readme_content += "### 4. **Lectures**\nVarious lecture examples on Monte Carlo methods for solving problems such as the Exponential Distribution and Efficiency calculations.\n\n"
    readme_content += "### 5. **Old Codes**\nOlder code snippets and experiments from past years.\n\n"
    readme_content += "### 6. **TGenPhaseSpace**\nContains files related to the TGenPhaseSpace library and its usage in phase space generation and particle decay simulations.\n\n"
    
    readme_content += "## Installation\n\n"
    readme_content += "To use the codes, clone this repository and open the `.cpp` files using your preferred C++ IDE (e.g., Visual Studio Code, CLion, or any other IDE). Ensure you have a C++ compiler (such as g++) installed to compile and run the code.\n\n"
    readme_content += "```bash\n"
    readme_content += "git clone <repository-url>\n"
    readme_content += "cd MC_Codes\n"
    readme_content += "```\n"

    readme_content += "## Usage\n\n"
    readme_content += "For each problem, run the corresponding `.cpp` file. For example, to run the Birthday Paradox simulation:\n\n"
    readme_content += "```bash\n"
    readme_content += "g++ For\\ Fun/BirthdayParadox.cpp -o BirthdayParadox\n"
    readme_content += "./BirthdayParadox\n"
    readme_content += "```\n"

    readme_content += "## License\n\nInclude the relevant license details here (if applicable).\n"

    return readme_content

def save_readme():
    readme_content = generate_readme()
    with open("README.md", "w") as readme_file:
        readme_file.write(readme_content)

if __name__ == "__main__":
    save_readme()
