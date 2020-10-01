﻿# include <Siv3D.hpp>

enum {
    BLOCK_Y = 5,
    BLOCK_X = 20,
};

void Main()
{
    // ブロックのサイズ
    constexpr Size blockSize(40, 20);

    // ブロックの配列
    Array<Rect> blocks;

    //ブロックの位置を判定するための準備
    bool BlockJudgment[BLOCK_Y][BLOCK_X] = {1,1,0,1,1,  0,1,1,1,0,  0,1,0,0,1,   0,1,1,1,0,
                                            1,1,0,1,1,  0,0,1,0,0,  0,1,0,1,0,   0,0,1,0,0,
                                            1,0,1,0,1,  0,0,1,0,0,  0,1,1,0,0,   0,0,1,0,0,
                                            1,0,0,0,1,  0,0,1,0,0,  0,1,0,1,0,   0,0,1,0,0,
                                            1,0,0,0,1,  0,1,1,1,0,  0,1,0,0,1,   0,1,1,1,0,};

    // 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
    for (auto p : step(Size((int)BLOCK_X, (int)BLOCK_Y)))
    {
        if (BlockJudgment[p.y][p.x]) {
            blocks << Rect(p.x * blockSize.x, 60 + p.y * blockSize.y, blockSize);
        }   
     }

    // ボールの速さ
    constexpr double speed = 480.0;

    // ボールの速度
    Vec2 ballVelocity(0, -speed);

    // ボール
    Circle ball(400, 400, 8);

    while (System::Update())
    {
        // パドル
        const Rect paddle(Arg::center(Cursor::Pos().x, 500), 60, 10);

        // ボールを移動
        ball.moveBy(ballVelocity * Scene::DeltaTime());

        // ブロックを順にチェック
        for (auto it = blocks.begin(); it != blocks.end(); ++it)
        {
            // ボールとブロックが交差していたら
            if (it->intersects(ball))
            {
                // ボールの向きを反転する
                (it->bottom().intersects(ball) || it->top().intersects(ball) ? ballVelocity.y : ballVelocity.x) *= -1;

                // ブロックを配列から削除（イテレータが無効になるので注意）
                blocks.erase(it);

                // これ以上チェックしない  
                break;
            }
        }

        // 天井にぶつかったらはね返る
        if (ball.y < 0 && ballVelocity.y < 0)
        {
            ballVelocity.y *= -1;
        }

        // 左右の壁にぶつかったらはね返る
        if ((ball.x < 0 && ballVelocity.x < 0) || (Scene::Width() < ball.x && ballVelocity.x > 0))
        {
            ballVelocity.x *= -1;
        }

        // パドルにあたったらはね返る
        if (ballVelocity.y > 0 && paddle.intersects(ball))
        {
            // パドルの中心からの距離に応じてはね返る向きを変える
            ballVelocity = Vec2((ball.x - paddle.center().x) * 10, -ballVelocity.y).setLength(speed);
        }

        // すべてのブロックを描画する
        for (const auto& block : blocks)
        {
            block.stretched(-1).draw(HSV(block.y - 40));
        }

        // ボールを描く
        ball.draw();

        // パドルを描く
        paddle.draw();
    }
}