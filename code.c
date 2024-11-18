#include <stdio.h>
#include <string.h>

#define MAX_QUESTIONS 50
#define MAX_OPTIONS 4

// Structure to hold quiz question and answer options
typedef struct {
    int question_id;
    char question_text[256];
    char options[MAX_OPTIONS][100];  // Four options for each question
    char correct_answer;             // Store the correct answer as 'A', 'B', 'C', or 'D'
} QuizQuestion;

// Structure to hold student response to each question
typedef struct {
    int question_id;
    char selected_answer;
} StudentResponse;

// Structure to hold the complete quiz
typedef struct {
    QuizQuestion questions[MAX_QUESTIONS];
    int question_count;
} Quiz;

// Function declarations
void createQuiz(Quiz *quiz);
void takeQuiz(Quiz *quiz, StudentResponse *responses, int *response_count);
int gradeQuiz(Quiz *quiz, StudentResponse *responses, int response_count);
void displayMenu();

int main() {
    Quiz quiz = { .question_count = 0 };
    StudentResponse responses[MAX_QUESTIONS];
    int response_count = 0;
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createQuiz(&quiz);
                break;
            case 2:
                takeQuiz(&quiz, responses, &response_count);
                break;
            case 3:
                if (response_count > 0) {
                    int score = gradeQuiz(&quiz, responses, response_count);
                    printf("Your score is: %d out of %d\n", score, quiz.question_count);
                } else {
                    printf("No responses found. Please take the quiz first.\n");
                }
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Function to display the main menu
void displayMenu() {
    printf("\n--- Online Quiz Application ---\n");
    printf("1. Create Quiz\n");
    printf("2. Take Quiz\n");
    printf("3. Grade Quiz\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Function to create a quiz by entering questions, options, and correct answers
void createQuiz(Quiz *quiz) {
    printf("Enter the number of questions: ");
    scanf("%d", &quiz->question_count);

    for (int i = 0; i < quiz->question_count; i++) {
        getchar(); // Clear newline from buffer
        printf("Enter question %d: ", i + 1);
        fgets(quiz->questions[i].question_text, 256, stdin);
        quiz->questions[i].question_id = i + 1;

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("Option %c: ", 'A' + j);
            fgets(quiz->questions[i].options[j], 100, stdin);
            // Remove newline character
            quiz->questions[i].options[j][strcspn(quiz->questions[i].options[j], "\n")] = '\0';
        }

        printf("Enter the correct answer (A/B/C/D): ");
        scanf(" %c", &quiz->questions[i].correct_answer);
    }
}

// Function to take a quiz by allowing a student to select answers for each question
void takeQuiz(Quiz *quiz, StudentResponse *responses, int *response_count) {
    printf("\n--- Taking Quiz ---\n");

    for (int i = 0; i < quiz->question_count; i++) {
        printf("Question %d: %s", i + 1, quiz->questions[i].question_text);

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("%c. %s\n", 'A' + j, quiz->questions[i].options[j]);
        }

        printf("Enter your answer (A/B/C/D): ");
        responses[i].question_id = quiz->questions[i].question_id;
        scanf(" %c", &responses[i].selected_answer);
        (*response_count)++;
    }
}

// Function to grade the quiz by comparing student responses with correct answers
int gradeQuiz(Quiz *quiz, StudentResponse *responses, int response_count) {
    int score = 0;

    for (int i = 0; i < response_count; i++) {
        int question_id = responses[i].question_id - 1;

        if (responses[i].selected_answer == quiz->questions[question_id].correct_answer) {
            score++;
        }
    }
    return score;
}
