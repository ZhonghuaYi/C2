#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

typedef struct
{
    struct subjectinfo* prev;
    struct subjectinfo* next;
    char name[10];
    int grade;
}subjectinfo;


typedef struct
{
    struct stuinfo * prev;
    struct stuinfo * next;
    char name[10];
    subjectinfo* subject;
    int sum_grade;
}stuinfo;

//�ɼ����
stuinfo* sum(stuinfo * stu) {
    stuinfo* p = stu;
    while (p->subject->grade)
    {
        p->sum_grade += p->subject->grade;
        if (p->subject->next) {
            p->subject = p->subject->next;
        }
        else
        {
            break;
        }
    }
    while (p->next)
    {
        p = p->next;
        while (p->subject->grade)
        {
            p->sum_grade += p->subject->grade;
            if (p->subject->next) {
                p->subject = p->subject->next;
            }
            else
            {
                break;
            }
        }
    }
    return stu;
}

//Ϊһ��ѧ����ӻ��޸Ŀ�Ŀ�ͳɼ�
stuinfo* add_or_change_grade(stuinfo* stu, char* name, char* subject, int grade) {
    stuinfo* p = stu;
    if (!strcmp(name, p->name)) {
        while (p->subject) {
            if (p->subject->name == subject) {
                p->subject->grade = grade;
                sum(stu);
                return stu;
            }
            if(p->subject->next){
                p->subject = p->subject->next;
            }
            else {
                break;
            }
        }
        if (!(p->subject)) {
            p->subject = (subjectinfo*)malloc(sizeof(subjectinfo));
            strcpy(p->subject->name, subject);
            p->subject->grade = grade;
            p->subject->next = NULL;
            sum(stu);
            return stu;
        }
        subjectinfo* new_subject = (subjectinfo*)malloc(sizeof(subjectinfo));
        p->subject->next = new_subject;
        new_subject->prev = p->subject;
        new_subject->next = NULL;
        strcpy(new_subject->name, subject);
        new_subject->grade = grade;
    }

    while (p->next) {
        p = p->next;
        if (!strcmp(name, p->name)) {
            while (p->subject) {
                if (p->subject->name == subject) {
                    p->subject->grade = grade;
                    sum(stu);
                    return stu;
                }
                if (p->subject->next) {
                    p->subject = p->subject->next;
                }
                else {
                    break;
                }
            }
            if (!(p->subject)) {
                p->subject = (subjectinfo*)malloc(sizeof(subjectinfo));
                strcpy(p->subject->name, subject);
                p->subject->grade = grade;
                p->subject->next = NULL;
                sum(stu);
                return stu;
            }
            subjectinfo* new_subject = (subjectinfo*)malloc(sizeof(subjectinfo));
            p->subject->next = new_subject;
            new_subject->prev = p->subject;
            new_subject->next = NULL;
            strcpy(new_subject->name, subject);
            new_subject->grade = grade;
        }
    }
    sum(stu);
    return stu;
}

//Ϊһ��ѧ��ɾ����Ŀ�ͳɼ�
stuinfo* delete_grade(stuinfo* stu, char* name, char* subject) {
    stuinfo* p = stu;
    if (!strcmp(p->name, name)) {
        while (p->subject->name) {
            if (p->subject->name == subject) {
                subjectinfo* prev = p->subject->prev;
                subjectinfo* next = p->subject->next;
                prev->next = next;
                next->prev = prev;
                free(p->subject);
                sum(stu);
                return stu;
            }
            if (p->subject->next) {
                p->subject = p->subject->next;
            }
            else {
                break;
            }
        }
    }
    while (p->next) {
        p = p->next;
        if (!strcmp(p->name, name)) {
            while (p->subject->name) {
                if (p->subject->name == subject) {
                    subjectinfo* prev = p->subject->prev;
                    subjectinfo* next = p->subject->next;
                    prev->next = next;
                    next->prev = prev;
                    free(p->subject);
                    sum(stu);
                    return stu;
                }
                if (p->subject->next) {
                    p->subject = p->subject->next;
                }
                else {
                    break;
                }
            }
        }
    }
    sum(stu);
    return stu;
}

//���һ��ѧ����Ϣ
stuinfo* add_student(stuinfo* stu, char* name) {
    stuinfo* p = stu;
    if (strlen(p->name) == 0) {
        strcpy(p->name, name);
        return stu;
    }
    while (p->next)
    {
        p = p->next;
    }
    stuinfo* new_stu = (stuinfo*)malloc(sizeof(stuinfo));
    strcpy(new_stu->name, name);
    new_stu->sum_grade = 0;
    new_stu->subject = NULL;
    new_stu->prev = p;
    new_stu->next = NULL;
    p->next = new_stu;
    return stu;
}

//ɾ��һ��ѧ����Ϣ
stuinfo* delete_student(stuinfo* stu, char* name) {
    stuinfo* p = stu;
    if (!strcmp(p->name, name)) {
        if (p->next) {
            stu = p->next;
        }
        else
        {
            char temp[10] = { 0 };
            strcpy(p->name, temp);
            p->sum_grade = 0;
        }
    }
    while (p->next)
    {
        p = p->next;
        if (!strcmp(p->name, name)) {
            if (p->next) {
                stu = p->next;
            }
            else
            {
                char temp[10] = { 0 };
                strcpy(p->name, temp);
                strcpy(p->name, '\0');
                p->sum_grade = 0;
            }
        }
    }
    return stu;
}

//��ʾѧ����Ϣ
stuinfo* show(stuinfo* stu) {
    stuinfo* p = stu;
    if (strlen(p->name) == 0) {
        printf("��ѧ��\n");
        return stu;
    }
    printf("%s :\n", p->name);
    if (p->subject == NULL) {
        printf("\t��ѧ����Ϣ\n");
        return stu;
    }
    else{
        printf("\t�ܳɼ�: %d\n", p->sum_grade);
        printf("\t%s %d\n", p->subject->name, p->subject->grade);
        while (p->subject->next) {
            p = p->subject;
            printf("\t%s %d\n", p->subject->name, p->subject->grade);
        }
    }
    while (p->next) {
        p = p->next;
        printf("%s :\n", p->name);
        if (p->subject == NULL) {
            printf("\t��ѧ����Ϣ\n");
            return stu;
        }
        else {
            printf("\t�ܳɼ�: %d\n", p->sum_grade);
            printf("\t%s %d\n", p->subject->name, p->subject->grade);
            while (p->subject->next) {
                p = p->subject;
                printf("\t%s %d\n", p->subject->name, p->subject->grade);
            }
        }
    }
    return stu;
}

int main() {
    stuinfo new_stu = {
        .next = NULL,
        .name = {0},
        .sum_grade = 0,
        .subject = NULL
    };
    stuinfo* stu = &new_stu;
    char name[10], subject[10];
    int grade;
    while (1)
    {
        //��������
        fflush(stdin);
        printf("ѡ������Ҫ���е�ѡ�\n1��չʾѧ����Ϣ\n2�����ѧ��\n3����ӻ��޸�ѧ����ѧ�Ƴɼ�\n4��ɾ��һ��ѧ����ѧ�Ƴɼ�\n5��ɾ��һ��ѧ����Ϣ\n6���˳�\n");
        char choice = getchar();
        if (choice == '6')
            break;
        switch (choice)
        {
        case('1'):
            show(stu);
            break;
        case('2'):
            printf("����ѧ�����֣�\n");
            scanf("%s", &name);
            stu = add_student(stu, name);
            printf("�ɹ���\n");
            break;
        case('3'):
            printf("����ѧ�����֡�ѧ�Ƶ����ƺͳɼ���\n");
            scanf("%s %s %d", &name, &subject, &grade);
            stu = add_or_change_grade(stu, name, subject, grade);
            printf("�ɹ���\n");
            break;
        case('4'):
            printf("����ѧ�����֡�ɾ����ѧ�Ƶ����ƣ�\n");
            scanf("%s %s", &name, &subject);
            stu = delete_grade(stu, name, subject);
            printf("�ɹ���\n");
            break;
        case('5'):
            printf("����ɾ����ѧ�����֣�\n");
            scanf("%s", &name);
            stu = delete_student(stu, name);
            printf("�ɹ���\n");
            break;
        default:
            break;
        }
        //��ȡ�س�������ֹ�������Ŀ¼
        getchar();
    }
    return 0;
}
