CREATE TABLE IF NOT EXISTS reg_student_hist(
    cnetid VARCHAR(32),
    courseid VARCHAR(32),
    year SMALLINT,
    quarter VARCHAR(6),
    grade VARCHAR(4),
    PRIMARY KEY (cnetid, courseid, year, quarter)
);
