#include <sm_moveit_screw_loop/clients/move_group_interface_client/components/cp_constraint_virtual_side_wall.h>

namespace sm_moveit_screw_loop
{
    namespace cl_move_group_interface
    {
        // Adds two simetric collision virtual walls for the moveit planning

        void CpConstraintVirtualSideWall::enable()
        {
            enabled_ = true;
            alreadyRemoved_ = false;
            this->update();
        }

        void CpConstraintVirtualSideWall::disable()
        {
            enabled_ = false;
            this->update();
        }

        CpConstraintVirtualSideWall::CpConstraintVirtualSideWall(std::string referenceFrame,  geometry_msgs::Vector3 size, geometry_msgs::Vector3 offset)
        {
            referenceFrame_ = referenceFrame;
            size_ = size;
            offset_ = offset;
            this->setUpdatePeriod(ros::Duration(10.0)); // do not update too much frequenfly since we have a relative collision
        }

        void CpConstraintVirtualSideWall::onInitialize()
        {
            this->requiresClient(movegroupclient_);
            planningSceneInterface_ = &movegroupclient_->planningSceneInterface;
        }

        void CpConstraintVirtualSideWall::update()
        {
            if (enabled_)
            {
                auto time = ros::Time::now();
                std::vector<moveit_msgs::CollisionObject> collisionObjects;
                createVirtualCollisionWalls(collisionObjects, time, moveit_msgs::CollisionObject::ADD);
                this->planningSceneInterface_->applyCollisionObjects(collisionObjects);
            }
            else if (alreadyRemoved_)
            {
                auto time = ros::Time::now();
                std::vector<moveit_msgs::CollisionObject> collisionObjects;

                createVirtualCollisionWalls(collisionObjects, time, moveit_msgs::CollisionObject::REMOVE);
                this->planningSceneInterface_->applyCollisionObjects(collisionObjects);
                alreadyRemoved_ = false;
            }
        }

        void CpConstraintVirtualSideWall::createCollisionBox(float x, float y, float z, float xl, float yl, float zl, std::string id, std::string frameid, moveit_msgs::CollisionObject &collision, const ros::Time &time, int addOrRemove)
        {
            collision.operation = addOrRemove;
            collision.id = id;

            collision.primitives.resize(1);
            collision.primitives[0].type = collision.primitives[0].BOX;
            collision.primitives[0].dimensions.resize(3);

            collision.primitives[0].dimensions[0] = xl;
            collision.primitives[0].dimensions[1] = yl;
            collision.primitives[0].dimensions[2] = zl;

            collision.primitive_poses.resize(1);
            collision.primitive_poses[0].position.x = x;
            collision.primitive_poses[0].position.y = y;
            collision.primitive_poses[0].position.z = z;
            collision.primitive_poses[0].orientation.w = 1.0;

            collision.header.frame_id = frameid;
            collision.header.stamp = time;
        }

        void CpConstraintVirtualSideWall::createVirtualCollisionWalls(std::vector<moveit_msgs::CollisionObject> &collisions, const ros::Time &time, int addOrRemove)
        {
            moveit_msgs::CollisionObject box;
            createCollisionBox(offset_.x, offset_.y , offset_.z, size_.x, size_.y, size_.z, "virtual_side_wall", referenceFrame_, box, time, addOrRemove);
            collisions.push_back(box);
        }

} // namespace sm_moveit_screw_loop

} // namespace sm_moveit_screw_loop